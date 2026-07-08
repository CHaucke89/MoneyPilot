from openpilot.common.params import Params


class LongitudinalMpcExt:
  def __init__(self, dt=None):
    self._params = Params()

  def get_stop_distance(self) -> float:
    from openpilot.selfdrive.controls.lib.longitudinal_mpc_lib.long_mpc import STOP_DISTANCE

    if self._params.get_bool("CustomStopDistanceEnabled"):
      return float(self._params.get("CustomStopDistance", return_default=True))

    return STOP_DISTANCE
