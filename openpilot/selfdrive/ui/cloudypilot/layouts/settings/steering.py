
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.sunnypilot.widgets.list_view import option_item_sp, LineSeparatorSP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.steering import SteeringLayoutSP
if gui_app.cloudypilot_ui():
  from openpilot.system.ui.cloudypilot.widgets.list_view import LineSeparatorCP as LineSeparatorSP



class SteeringLayoutCP(SteeringLayoutSP):
  def __init__(self):
    super().__init__()

  def _initialize_items(self):
    items = super()._initialize_items()

    self._custom_sr = option_item_sp(
      param="CustomSR",
      title=lambda: tr("Custom Steer Ratio"),
      min_value=1000,
      max_value=2000,
      value_change_step=10,
      use_float_scaling=True,
      description=lambda: tr("Set a custom steer ratio value."),
      label_callback=lambda sr: f'{sr / 100.0:.2f}'
    )

    items += [
      self._custom_sr,
      LineSeparatorSP(40),
    ]
    return items
