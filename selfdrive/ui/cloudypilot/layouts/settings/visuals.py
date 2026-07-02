from openpilot.common.params import UnknownKeyName
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.sunnypilot.widgets.list_view import toggle_item_sp
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.visuals import VisualsLayout
from openpilot.system.ui.lib.multilang import tr



class VisualsLayoutCP(VisualsLayout):
  def __init__(self):
    self._toggles = {}
    self._toggle_defs = {}
    super().__init__()

  def _initialize_items(self):
    items = super()._initialize_items()
    _insert_below = {}

    # Add new toggle syntax:
    # self._toggle_defs["NewParam"] = (title, desc, icon, needs_restart)
    # _insert_below["NewParam"] = "InsertBelowThisParam"

    self._toggle_defs["TorqueBarFade"] = (lambda: tr("Steering Arc Fade"),
        tr("Enable or disable the fade at the bottom of the onroad screen with Steering Arc enabled."),
        None, False, None)
    _insert_below["TorqueBarFade"] = "TorqueBar"

    self._toggle_defs["UseImperial"] = (lambda: tr("Use Imperial"),
        tr("Use imperial units (ft) for altitude."),
        None, False, None)
    _insert_below["UseImperial"] = "RocketFuel"

    for param, after in _insert_below.items():
      title, desc, icon, callback, _ = self._toggle_defs[param]
      toggle = toggle_item_sp(
        title=title,
        description=desc,
        param=param,
        initial_state=ui_state.params.get_bool(param),
        icon=icon,
        callback=callback,
      )
      self._toggles[param] = toggle

      try:
        locked = self._params.get_bool(param + "Lock")
      except UnknownKeyName:
        locked = False

      toggle.action_item.set_enabled(not locked)
      if locked:
        self._locked_toggles.add(param)

      # Insert toggle in items list at the desired position
      insert_index = next(i for i, item in enumerate(items) if item is self._toggles[after])
      items = items[:insert_index + 1] + [toggle] + items[insert_index + 1:]

    return items

  def _update_state(self):
    super()._update_state()

    torque_bar_enabled = ui_state.params.get_bool("TorqueBar")
    self._toggles["TorqueBarFade"].set_enabled(torque_bar_enabled)
    self._toggles["TorqueBarFade"].set_visible(torque_bar_enabled)
    if not torque_bar_enabled:
      ui_state.params.put_bool("TorqueBarFade", torque_bar_enabled)
