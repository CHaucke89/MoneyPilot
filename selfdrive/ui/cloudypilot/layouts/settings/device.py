from openpilot.selfdrive.ui.sunnypilot.layouts.settings.device import DeviceLayoutSP
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.sunnypilot.widgets.list_view import option_item_sp

class DeviceLayoutCP(DeviceLayoutSP):
  def _initialize_items(self):
    items = super()._initialize_items()

    self._low_voltage_shutdown = option_item_sp(
      title=lambda: tr("Low Voltage Shutdown"),
      description=lambda: tr("Device will shutdown if car battery reaches set voltage."),
      param="CustomShutdownVoltage",
      min_value=1170,
      max_value=1280,
      value_change_step=10,
      on_value_changed=None,
      enabled=True,
      icon="",
      value_map=None,
      label_width=360,
      use_float_scaling=True,
      inline=True,
      label_callback=self._update_low_voltage_shutdown_label
    )

    # Insert into items list
    low_voltage_index = next(i for i, item in enumerate(items) if item is self._max_time_offroad)
    insert_pos = low_voltage_index + 2

    items = items[:insert_pos] + [
      self._low_voltage_shutdown,
    ] + items[insert_pos:]

    return items

  @staticmethod
  def _update_low_voltage_shutdown_label(value: int) -> str:
    label = tr("Disabled") if value == 1170 else f"{value / 100}" + tr("V")
    label += tr(" (Default)") if value == 1180 else ""
    return label

