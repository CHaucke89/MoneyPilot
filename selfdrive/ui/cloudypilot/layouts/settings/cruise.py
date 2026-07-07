from openpilot.selfdrive.ui.sunnypilot.layouts.settings.cruise import CruiseLayout
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.sunnypilot.widgets.list_view import toggle_item_sp
from openpilot.system.ui.cloudypilot.lib.styles import style
from openpilot.system.ui.cloudypilot.widgets.list_view import option_item_cp


class CruiseLayoutCP(CruiseLayout):
  def __init__(self):
    super().__init__()

  def _initialize_items(self):
    items = super()._initialize_items()

    self.stop_distance_toggle = toggle_item_sp(
      title=tr("Use Custom Stop Distance"),
      description="",
      param="CustomStopDistanceEnabled",
      callback=self._on_custom_stop_distance_toggle)

    self.stop_distance = option_item_cp(tr("Custom Stop Distance"), "CustomStopDistance", 100, 1000,
                                                  tr("Set a custom stopping distance from the lead vehicle."),
                                                  1, None, True, "", style.BUTTON_ACTION_WIDTH, None, True,
                                                  lambda v: f"{v / 100:.2f}m", True, True)

    for ctrl, key in [(self.stop_distance, "CustomStopDistance"),]:
      ctrl.action_item.set_value(int(float(ui_state.params.get(key, return_default=True)) * 100))

    items.extend([self.stop_distance_toggle,
                  self.stop_distance])

    return items

  def _update_state(self):
    super()._update_state()
    self._on_custom_stop_distance_toggle(self.stop_distance_toggle.action_item.get_state())

  def _on_custom_stop_distance_toggle(self, state):
    self.stop_distance.set_visible(state)
    self.stop_distance.action_item.set_enabled(self.stop_distance_toggle.action_item.enabled)

