
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.developer import DeveloperLayoutSP
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.widgets import DialogResult
from openpilot.system.ui.widgets.confirm_dialog import ConfirmDialog

from openpilot.system.ui.sunnypilot.widgets.list_view import toggle_item_sp



class DeveloperLayoutCP(DeveloperLayoutSP):
  def _initialize_items(self):
    super()._initialize_items()

    self.konik_toggle = toggle_item_sp(tr("Use Konik API"), tr("Use Konik's API rather than comma's. Requires reboot."), param="KonikApi",
                                       callback=self._on_konik_toggled)
    self.items.append(self.konik_toggle)

    return self.items

  def _perform_reboot(self, result):
    if result == DialogResult.CONFIRM:
      ui_state.params.put_bool("DoSoftReboot", True)

  def _on_konik_toggled(self, result):
    dialog = ConfirmDialog(tr("Soft reboot required for changes to take effect. Soft reboot now?"), tr("Soft Reboot"), callback=self._perform_reboot)
    gui_app.push_widget(dialog)

  def _update_state(self):
    show_advanced = ui_state.params.get_bool("ShowAdvancedControls")
    self.konik_toggle.set_visible(show_advanced)
