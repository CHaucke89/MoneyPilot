from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.device import DeviceLayoutSP
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.widgets import DialogResult
from openpilot.system.ui.cloudypilot.widgets.list_view import option_item_cp
from openpilot.system.ui.widgets.confirm_dialog import ConfirmDialog, alert_dialog
from openpilot.system.ui.sunnypilot.widgets.list_view import dual_button_item_sp, LineSeparator

class DeviceLayoutCP(DeviceLayoutSP):
  def _initialize_items(self):
    items = super()._initialize_items()

    self._low_voltage_shutdown = option_item_cp(
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
      reset_enabled=True,
      label_callback=self._update_low_voltage_shutdown_label
    )

    self._soft_reboot_btn = dual_button_item_sp(
      left_text=lambda: tr("Soft Reboot"),
      left_callback=self._soft_reboot_prompt,
      right_text="",
      right_callback=None
    )
    self._soft_reboot_btn.action_item.right_button.set_visible(False)

    # Find index of max time offroad and insert directly below
    low_voltage_index = next(i for i, item in enumerate(items) if item is self._max_time_offroad)
    insert_pos = low_voltage_index + 2

    items = items[:insert_pos] + [
      self._low_voltage_shutdown,
      LineSeparator(),
    ] + items[insert_pos:]

    items.append(self._soft_reboot_btn)

    return items

  @staticmethod
  def _update_low_voltage_shutdown_label(value: int) -> str:
    label = tr("Disabled") if value == 1170 else f"{value / 100}" + tr("V")
    label += tr(" (Default)") if value == 1180 else ""
    return label

  def _soft_reboot_prompt(self):
    if ui_state.engaged:
      gui_app.push_widget(alert_dialog(tr("Disengage to Soft Reboot")))
      return

    def perform_soft_reboot(result: DialogResult):
      if not ui_state.engaged and result == DialogResult.CONFIRM:
        self._params.put_bool_nonblocking("DoSoftReboot", True)

    dialog = ConfirmDialog(tr("Are you sure you want to soft reboot?"), tr("Soft Reboot"), callback=perform_soft_reboot)
    gui_app.push_widget(dialog)
