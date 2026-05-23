#!/usr/bin/env python3
"""Dump current learned torque values from Params.

Prints both:
  - global single-value learner (LiveTorqueParameters, always running)
  - speed-binned learner (only populated when SpeedDependentTorqueToggle is ON
    and the new PR is applied)

Also saves a timestamped backup of the raw cereal blob under
/data/torque_backups/ (persistent across reboots), suitable for restoring with:

    python3 -c "from openpilot.common.params import Params; \\
      Params().put('LiveTorqueParameters', open('<file>.bytes', 'rb').read())"
"""

from __future__ import annotations

import json
import os
import sys
import time

from openpilot.common.params import Params
from cereal import car, log


BACKUP_DIR = "/data/torque_backups"


def _load_carparams():
  raw = Params().get("CarParams") or Params().get("CarParamsPrevRoute")
  if not raw:
    return None
  with car.CarParams.from_bytes(raw) as cp:
    out = {
      "carFingerprint": cp.carFingerprint,
      "brand": cp.brand,
      "lateralTuningKind": cp.lateralTuning.which(),
    }
    if cp.lateralTuning.which() == "torque":
      t = cp.lateralTuning.torque
      out["offline_latAccelFactor"] = t.latAccelFactor
      out["offline_latAccelOffset"] = t.latAccelOffset
      out["offline_friction"] = t.friction
    return out


def _load_ltp():
  raw = Params().get("LiveTorqueParameters")
  if not raw:
    return None, None
  with log.Event.from_bytes(raw) as evt:
    ltp = evt.liveTorqueParameters
    snap = {
      "version": ltp.version,
      "liveValid": ltp.liveValid,
      "useParams": ltp.useParams,
      "calPerc": ltp.calPerc,
      "decay": ltp.decay,
      "maxResets": ltp.maxResets,
      "totalBucketPoints": ltp.totalBucketPoints,
      "latAccelFactorFiltered": ltp.latAccelFactorFiltered,
      "latAccelOffsetFiltered": ltp.latAccelOffsetFiltered,
      "frictionCoefficientFiltered": ltp.frictionCoefficientFiltered,
      "latAccelFactorRaw": ltp.latAccelFactorRaw,
      "latAccelOffsetRaw": ltp.latAccelOffsetRaw,
      "frictionCoefficientRaw": ltp.frictionCoefficientRaw,
      "num_points": len(ltp.points),
    }
    try:
      snap["speedBinCenters"] = list(ltp.speedBinCenters)
      snap["speedBinLatAccelFactors"] = list(ltp.speedBinLatAccelFactors)
      snap["speedBinFrictions"] = list(ltp.speedBinFrictions)
      snap["speedBinValid"] = list(ltp.speedBinValid)
      raw_points = list(ltp.speedBinPoints)
      snap["speedBinPoints"] = [[list(pt) for pt in bin_pts] for bin_pts in raw_points]
      snap["speedBinHasPoints"] = len(raw_points) > 0
    except Exception:
      snap["speedBinCenters"] = None
    return raw, snap


def _print_header(title: str) -> None:
  print()
  print("=" * 60)
  print(f"  {title}")
  print("=" * 60)


def _print_carparams(cp) -> None:
  _print_header("Car identity")
  if cp is None:
    print("  (no CarParams stored — car never onboarded)")
    return
  print(f"  fingerprint:           {cp['carFingerprint']}")
  print(f"  brand:                 {cp['brand']}")
  print(f"  lateral controller:    {cp['lateralTuningKind']}")
  if cp['lateralTuningKind'] == "torque":
    print(f"  offline latAccelFactor:{cp['offline_latAccelFactor']:>8.4f}  (baked-in default)")
    print(f"  offline friction:      {cp['offline_friction']:>8.4f}")
    print(f"  offline latAccelOffset:{cp['offline_latAccelOffset']:>8.4f}")


def _print_toggles() -> None:
  _print_header("Relevant toggles")
  p = Params()
  toggles = [
    "LiveTorqueParamsToggle",
    "LiveTorqueParamsRelaxedToggle",
    "CustomTorqueParams",
    "TorqueParamsOverrideEnabled",
    "EnforceTorqueControl",
    "SpeedDependentTorqueToggle",
  ]
  for k in toggles:
    try:
      v = p.get_bool(k)
      mark = "ON " if v else "OFF"
      print(f"  [{mark}] {k}")
    except Exception:
      print(f"  [   ] {k}  (param key missing on this branch)")


def _print_global(ltp) -> None:
  _print_header("Global learner (LiveTorqueParameters)")
  if ltp is None:
    print("  No cache stored yet — either the toggle is OFF, learning has")
    print("  never run to completion, or Params was wiped.")
    return

  print(f"  version:               {ltp['version']}")
  print(f"  liveValid:             {ltp['liveValid']}")
  print(f"  useParams:             {ltp['useParams']}  (controller is actually using these values?)")
  print(f"  calPerc:               {ltp['calPerc']}%")
  print(f"  totalBucketPoints:     {ltp['totalBucketPoints']:.0f}")
  print(f"  maxResets:             {ltp['maxResets']:.0f}")
  print(f"  decay:                 {ltp['decay']:.2f}  (max = 250.0)")
  print()
  print("  -- Filtered (active learned values) --")
  print(f"  latAccelFactorFiltered:     {ltp['latAccelFactorFiltered']:.4f}")
  print(f"  latAccelOffsetFiltered:     {ltp['latAccelOffsetFiltered']:.4f}")
  print(f"  frictionCoefficientFiltered:{ltp['frictionCoefficientFiltered']:.4f}")
  print()
  print("  -- Raw (last SVD fit, un-smoothed) --")
  print(f"  latAccelFactorRaw:          {ltp['latAccelFactorRaw']:.4f}")
  print(f"  latAccelOffsetRaw:          {ltp['latAccelOffsetRaw']:.4f}")
  print(f"  frictionCoefficientRaw:     {ltp['frictionCoefficientRaw']:.4f}")
  print()
  print(f"  points stored:         {ltp['num_points']}")


def _print_speed_bins(ltp) -> None:
  _print_header("Speed-binned learner")
  if ltp is None:
    print("  (no cache)")
    return

  centers = ltp.get("speedBinCenters")
  if centers is None:
    print("  This branch's cereal schema doesn't have speedBin* fields")
    print("  — speed-dependent PR not applied.")
    return

  if not centers:
    print("  No speed-bin data published. Either:")
    print("    1. SpeedDependentTorqueToggle is OFF (most likely)")
    print("    2. torqued hasn't started up since the toggle was enabled")
    print("    3. The PR layer isn't running for some reason")
    return

  lafs = ltp["speedBinLatAccelFactors"]
  fris = ltp["speedBinFrictions"]
  valid = ltp["speedBinValid"]
  has_points = ltp["speedBinHasPoints"]
  points = ltp.get("speedBinPoints") or [[] for _ in centers]

  while len(points) < len(centers):
    points.append([])

  n_bins = len(centers)
  per_bin_totals = [len(bp) for bp in points]
  grand_total = sum(per_bin_totals)

  print(f"  bins:                  {n_bins}")
  print(f"  cache has point data:  {has_points}  (written every ~60s)")
  print(f"  total points (all bins): {grand_total}")
  print()
  print(f"  {'bin':>3}  {'center':>8}  {'mph':>8}  {'LAF':>8}  {'friction':>9}  {'points':>7}  {'valid':>7}")
  print(f"  {'---':>3}  {'------':>8}  {'------':>8}  {'------':>8}  {'-------':>9}  {'------':>7}  {'-----':>7}")
  for i, (c, l, f, v) in enumerate(zip(centers, lafs, fris, valid, strict=True)):
    mph = c * 2.237
    mark = "MATURED" if v else "  ...  "
    n_pts = per_bin_totals[i]
    print(f"  {i:>3}  {c:>8.2f}  {mph:>8.1f}  {l:>8.4f}  {f:>9.4f}  {n_pts:>7}  {mark:>7}")

  if grand_total == 0:
    print()
    print("  (no points stored in this cache snapshot — try again in ~60s)")
    return

  steer_bounds = [(-0.5, -0.3), (-0.3, -0.2), (-0.2, -0.1), (-0.1, 0.0),
                  (0.0, 0.1), (0.1, 0.2), (0.2, 0.3), (0.3, 0.5)]
  relaxed_base = [1, 200, 300, 500, 500, 300, 200, 1]
  min_pts = [max(b // n_bins, 1) for b in relaxed_base]
  min_total = sum(min_pts)

  print()
  print("  Per-bin steer-torque distribution (matures when EVERY sub-bucket meets its min):")
  print(f"  {'bin':>3}  " + " ".join(f"{lo:+.1f}/{hi:+.1f}".rjust(9) for lo, hi in steer_bounds) + "    status")
  print(f"  {'---':>3}  " + " ".join(f"min={m:>3}".rjust(9) for m in min_pts) + f"    (need {min_total} total)")
  for i, bin_pts in enumerate(points):
    sub_counts = [0] * 8
    for pt in bin_pts:
      steer = pt[0]
      for j, (lo, hi) in enumerate(steer_bounds):
        if lo <= steer < hi:
          sub_counts[j] += 1
          break
    meets = [sub_counts[j] >= min_pts[j] for j in range(8)]
    counts_str = " ".join(
      (f"\033[32m{c:>7}✓\033[0m" if ok else f"\033[33m{c:>7} \033[0m")
      for c, ok in zip(sub_counts, meets, strict=True)
    )
    total = sum(sub_counts)
    if all(meets) and total >= min_total:
      status = "\033[32mVALID\033[0m"
    else:
      missing_buckets = [j for j, ok in enumerate(meets) if not ok]
      if total < min_total:
        status = f"need {min_total - total} more, missing buckets {missing_buckets}"
      else:
        status = f"missing buckets {missing_buckets}"
    print(f"  {i:>3}  {counts_str}    {status}")


def _save_backup(raw: bytes, ltp) -> None:
  os.makedirs(BACKUP_DIR, exist_ok=True)
  ts = time.strftime("%Y%m%d_%H%M%S")

  raw_path = os.path.join(BACKUP_DIR, f"LiveTorqueParameters_{ts}.bytes")
  with open(raw_path, "wb") as f:
    f.write(raw)

  data: dict = {
    "captured_at": ts,
    "global": {
      "liveValid": ltp["liveValid"],
      "useParams": ltp["useParams"],
      "version": ltp["version"],
      "calPerc": ltp["calPerc"],
      "decay": ltp["decay"],
      "maxResets": ltp["maxResets"],
      "totalBucketPoints": ltp["totalBucketPoints"],
      "latAccelFactorFiltered": ltp["latAccelFactorFiltered"],
      "latAccelOffsetFiltered": ltp["latAccelOffsetFiltered"],
      "frictionCoefficientFiltered": ltp["frictionCoefficientFiltered"],
      "latAccelFactorRaw": ltp["latAccelFactorRaw"],
      "latAccelOffsetRaw": ltp["latAccelOffsetRaw"],
      "frictionCoefficientRaw": ltp["frictionCoefficientRaw"],
      "num_points": ltp["num_points"],
    },
  }

  centers = ltp.get("speedBinCenters") or []
  if centers:
    data["speed_bins"] = {
      "centers_mps": centers,
      "lat_accel_factors": ltp["speedBinLatAccelFactors"],
      "frictions": ltp["speedBinFrictions"],
      "valid": ltp["speedBinValid"],
    }

  json_path = os.path.join(BACKUP_DIR, f"LiveTorqueParameters_{ts}.json")
  with open(json_path, "w") as f:
    json.dump(data, f, indent=2)

  _print_header("Backup written")
  print(f"  raw:  {raw_path} ({len(raw):,} bytes)")
  print(f"  json: {json_path}")


def main() -> int:
  cp = _load_carparams()
  raw, ltp = _load_ltp()

  _print_carparams(cp)
  _print_toggles()
  _print_global(ltp)
  _print_speed_bins(ltp)
  if raw is not None and ltp is not None:
    _save_backup(raw, ltp)
  print()
  return 0


if __name__ == "__main__":
  sys.exit(main())
