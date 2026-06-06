from openpilot.common.params import UnknownKeyName
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.widgets.scroller_tici import Scroller
from openpilot.system.ui.sunnypilot.widgets.list_view import toggle_item_sp
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.visuals import VisualsLayout
from openpilot.system.ui.lib.multilang import tr



class VisualsLayoutCP(VisualsLayout):
  def __init__(self):
    super().__init__()

    self._toggle_defs |= {"TorqueBarFade": (lambda: tr("Steering Arc Fade"),
        tr("Enable or disable the fade at the bottom of the onroad screen with Steering Arc enabled."),
        None,
      ),
    }

    insert_after = {
      "TorqueBarFade": "TorqueBar",
    }

    self._toggles = {}
    for param, after in insert_after.items():
      for param, (title, desc, callback) in self._toggle_defs.items():
        toggle = toggle_item_sp(
          title=title,
          description=desc,
          param=param,
          initial_state=ui_state.params.get_bool(param),
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

      # Rebuild the dict and insert the new toggle(s) at the position specified by insert_after
      new_toggles = {}
      for key, value in self._toggles.items():
        new_toggles[key] = value
        if key == after:
          new_toggles[param] = toggle
      self._toggles = new_toggles

    self._scroller = Scroller(list(self._toggles.values()), line_separator=True, spacing=0)

  def _update_state(self):
    super()._update_state()

    torque_bar_enabled = ui_state.params.get_bool("TorqueBar")
    self._toggles["TorqueBarFade"].set_enabled(torque_bar_enabled)
    self._toggles["TorqueBarFade"].set_visible(torque_bar_enabled)
    if not torque_bar_enabled:
      ui_state.params.put_bool("TorqueBarFade", torque_bar_enabled)
