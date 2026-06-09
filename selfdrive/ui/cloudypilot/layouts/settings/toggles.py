from openpilot.common.params import UnknownKeyName
from openpilot.system.ui.widgets.scroller_tici import Scroller
from openpilot.selfdrive.ui.layouts.settings.toggles import DESCRIPTIONS, TogglesLayout
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.sunnypilot.widgets.list_view import toggle_item_sp



DESCRIPTIONS |= {
  "AlwaysOffDM": tr_noop("Disable driver monitoring even when cloudypilot is engaged."),
}


class TogglesLayoutCP(TogglesLayout):
  def __init__(self):
    super().__init__()
    insert_below = {}
    self._toggles = {}
    self._toggle_defs |= {}

    # New toggles go here. Syntax:
    # self._toggle_defs["NewParam"] = (title, desc, needs_restart)
    # insert_below["NewParam"] = "InsertBelowThisParam"
    self._toggle_defs["AlwaysOffDM"] = (lambda: tr("Always-Off Driver Monitoring"), DESCRIPTIONS["AlwaysOffDM"], None, False)
    insert_below["AlwaysOffDM"] = "AlwaysOnDM"

    for param, after in insert_below.items():
      for param, (title, desc, icon, needs_restart) in self._toggle_defs.items():
        toggle = toggle_item_sp(
          title=title,
          description=desc,
          param=param,
          initial_state=self._params.get_bool(param),
          icon=icon,
          callback=lambda state, p=param: self._toggle_callback(state, p),
        )
        self._toggles[param] = toggle

        try:
          locked = self._params.get_bool(param + "Lock")
        except UnknownKeyName:
          locked = False

        additional_desc = ""
        if needs_restart and not locked:
          additional_desc = tr("Changing this setting will restart sunnypilot if the car is powered on.")
        toggle.set_description(lambda og_desc=toggle.description, add_desc=additional_desc: tr(og_desc) + (" " + tr(add_desc) if add_desc else ""))

        toggle.action_item.set_enabled(not locked)
        if locked:
          self._locked_toggles.add(param)

      # Rebuild dict and insert new toggle at the desired position
      new_toggles = {}
      for key, value in self._toggles.items():
        new_toggles[key] = value
        if key == after:
          new_toggles[param] = toggle
      self._toggles = new_toggles

    self._scroller = Scroller(list(self._toggles.values()), line_separator=True, spacing=0)

  def _toggle_callback(self, state: bool, param: str):
    super()._toggle_callback(state, param)
    # Mutual exclusion to keep DM out of superposition if they're both toggled on :)
    if param == "AlwaysOnDM" and state:
      self._params.put_bool("AlwaysOffDM", not state)
      self._toggles["AlwaysOffDM"].action_item.set_state(not state)
    elif param == "AlwaysOffDM" and state:
      self._params.put_bool("AlwaysOnDM", not state)
      self._toggles["AlwaysOnDM"].action_item.set_state(not state)
