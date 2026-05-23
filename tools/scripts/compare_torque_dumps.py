#!/usr/bin/env python3
"""Compare two LiveTorqueParameters JSON dumps from dump_torque_state.py.

Use to decide if speed-dependent torque learning (PR #1776) actually helps
on this car: dump once with toggle OFF, drive a few hours, toggle ON, drive
a few more hours, dump again, compare.

Usage:
  compare_torque_dumps.py before.json after.json
  compare_torque_dumps.py            # auto-pick two most recent in /data/torque_backups/
"""

from __future__ import annotations

import glob
import json
import os
import sys


BACKUP_DIR = "/data/torque_backups"


def _load(path):
  with open(path) as f:
    return json.load(f)


def _auto_pick():
  files = sorted(glob.glob(os.path.join(BACKUP_DIR, "LiveTorqueParameters_*.json")))
  if len(files) < 2:
    print(f"need >=2 dumps in {BACKUP_DIR} (have {len(files)})")
    sys.exit(1)
  return files[-2], files[-1]


def _delta(a, b, fmt="{:+.4f}"):
  d = b - a
  return fmt.format(d)


def _print_global(a, b):
  print()
  print("=" * 60)
  print("  Global learner (single-LAF)")
  print("=" * 60)
  ag, bg = a["global"], b["global"]
  rows = [
    ("latAccelFactorFiltered",     ag["latAccelFactorFiltered"],     bg["latAccelFactorFiltered"]),
    ("latAccelOffsetFiltered",     ag["latAccelOffsetFiltered"],     bg["latAccelOffsetFiltered"]),
    ("frictionCoefficientFiltered",ag["frictionCoefficientFiltered"],bg["frictionCoefficientFiltered"]),
    ("latAccelFactorRaw",          ag["latAccelFactorRaw"],          bg["latAccelFactorRaw"]),
    ("latAccelOffsetRaw",          ag["latAccelOffsetRaw"],          bg["latAccelOffsetRaw"]),
    ("frictionCoefficientRaw",     ag["frictionCoefficientRaw"],     bg["frictionCoefficientRaw"]),
    ("totalBucketPoints",          ag["totalBucketPoints"],          bg["totalBucketPoints"]),
    ("decay",                      ag["decay"],                      bg["decay"]),
    ("maxResets",                  ag["maxResets"],                  bg["maxResets"]),
  ]
  print(f"  {'field':<32} {'before':>10} {'after':>10} {'delta':>10}")
  print(f"  {'-'*32} {'-'*10} {'-'*10} {'-'*10}")
  for k, va, vb in rows:
    print(f"  {k:<32} {va:>10.4f} {vb:>10.4f} {_delta(va, vb):>10}")

  # Raw vs Filtered divergence is the key signal: if raw consistently
  # differs from filtered, single LAF is fighting the data.
  raw_filt_a = abs(ag["latAccelFactorRaw"] - ag["latAccelFactorFiltered"])
  raw_filt_b = abs(bg["latAccelFactorRaw"] - bg["latAccelFactorFiltered"])
  print()
  print(f"  |raw - filtered| LAF:  before={raw_filt_a:.4f}  after={raw_filt_b:.4f}")
  pct_a = 100 * raw_filt_a / max(ag["latAccelFactorFiltered"], 1e-3)
  pct_b = 100 * raw_filt_b / max(bg["latAccelFactorFiltered"], 1e-3)
  print(f"  as %:                  before={pct_a:.1f}%   after={pct_b:.1f}%")
  if pct_b > 10:
    print(f"  -> raw/filtered split > 10% in 'after' — single LAF can't fit, speed-dep helps")
  elif pct_b < 3:
    print(f"  -> raw/filtered tight (<3%) — single LAF fits well, speed-dep adds nothing")


def _print_speed_bins(a, b):
  print()
  print("=" * 60)
  print("  Speed-binned learner")
  print("=" * 60)
  sa = a.get("speed_bins")
  sb = b.get("speed_bins")
  if not sb:
    print("  no speed_bins block in 'after' dump")
    print("  -> SpeedDependentTorqueToggle was OFF or PR not deployed when after-dump taken")
    return
  if not sa:
    print("  (before-dump had no speed_bins — comparing 'after' alone)")
    sa = {"centers_mps": sb["centers_mps"], "lat_accel_factors": [0.0]*len(sb["centers_mps"]),
          "frictions": [0.0]*len(sb["centers_mps"]), "valid": [False]*len(sb["centers_mps"])}

  centers = sb["centers_mps"]
  print(f"  {'bin':>3} {'center':>7} {'mph':>6} {'LAF_b':>8} {'LAF_a':>8} {'dLAF':>8} {'fri_b':>7} {'fri_a':>7} {'dfri':>8} {'valid_a':>8}")
  laf_after = []
  for i, c in enumerate(centers):
    mph = c * 2.237
    laf_a = sa["lat_accel_factors"][i] if i < len(sa["lat_accel_factors"]) else 0.0
    laf_b = sb["lat_accel_factors"][i]
    fri_a = sa["frictions"][i] if i < len(sa["frictions"]) else 0.0
    fri_b = sb["frictions"][i]
    valid_b = sb["valid"][i]
    laf_after.append(laf_b)
    mark = "MATURED" if valid_b else "  ...  "
    print(f"  {i:>3} {c:>7.2f} {mph:>6.1f} {laf_a:>8.4f} {laf_b:>8.4f} {_delta(laf_a, laf_b):>8} {fri_a:>7.4f} {fri_b:>7.4f} {_delta(fri_a, fri_b):>8} {mark:>8}")

  # Verdict: spread of per-bin LAFs vs global LAF
  global_laf = b["global"]["latAccelFactorFiltered"]
  diffs = [abs(l - global_laf) for l in laf_after]
  max_diff = max(diffs) if diffs else 0
  pct = 100 * max_diff / max(global_laf, 1e-3)
  print()
  print(f"  global LAF (after):    {global_laf:.4f}")
  print(f"  max |bin - global|:    {max_diff:.4f}  ({pct:.1f}%)")
  if pct > 10:
    print(f"  -> per-bin spread > 10% — speed-dep DOES help this car")
  elif pct < 3:
    print(f"  -> per-bin LAFs ≈ global (< 3%) — speed-dep adds nothing on this car, drop PR")
  else:
    print(f"  -> per-bin spread 3-10% — marginal, may need more drive time to mature")


def main() -> int:
  if len(sys.argv) == 1:
    before, after = _auto_pick()
    print(f"auto-picked:\n  before: {before}\n  after:  {after}")
  elif len(sys.argv) == 3:
    before, after = sys.argv[1], sys.argv[2]
  else:
    print(__doc__)
    return 1

  a = _load(before)
  b = _load(after)
  _print_global(a, b)
  _print_speed_bins(a, b)
  print()
  return 0


if __name__ == "__main__":
  sys.exit(main())
