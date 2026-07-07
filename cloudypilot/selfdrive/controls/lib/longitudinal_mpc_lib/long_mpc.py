#!/usr/bin/env python3
from cereal import log
from openpilot.common.params import Params
from openpilot.common.realtime import DT_MDL
import openpilot.selfdrive.controls.lib.longitudinal_mpc_lib.long_mpc as _long_mpc_mod
from openpilot.selfdrive.controls.lib.longitudinal_mpc_lib.long_mpc import LongitudinalMpc


class LongitudinalMpcCP(LongitudinalMpc):
  def __init__(self, dt=DT_MDL):
    self._params = Params()
    super().__init__(dt=dt)

  def update(self, radarstate, v_cruise, personality=log.LongitudinalPersonality.standard):
    val = self._params.get("CustomStopDistance")
    if val is not None:
      _long_mpc_mod.STOP_DISTANCE = float(val)
    super().update(radarstate, v_cruise, personality)
