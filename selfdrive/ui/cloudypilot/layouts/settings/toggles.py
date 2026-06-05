from openpilot.common.params import UnknownKeyName
from openpilot.system.ui.widgets.scroller_tici import Scroller
from openpilot.selfdrive.ui.layouts.settings.toggles import DESCRIPTIONS, TogglesLayout, toggle_item
from openpilot.system.ui.lib.multilang import tr, tr_noop


DESCRIPTIONS |= {
  "AlwaysOffDM": tr_noop("Disable driver monitoring even when cloudypilot is engaged."),
}


class TogglesLayoutCP(TogglesLayout):
  def __init__(self):
    super().__init__()

    self._toggle_defs |= {
      "AlwaysOffDM": (lambda: tr("Always-Off Driver Monitoring"), DESCRIPTIONS["AlwaysOffDM"], "monitoring.png", False),
    }

    # Create a dict to indicate where to insert the new toggle
    # Syntax: {NewParam: InsertBelowThisParam}
    insert_after = {
      "AlwaysOffDM": "AlwaysOnDM",
    }

    for param, after in insert_after.items():
      title, desc, icon, needs_restart = self._toggle_defs[param]

      toggle = toggle_item(title, desc, self._params.get_bool(param),
                           callback=lambda s, p=param: self._toggle_callback(s, p),
                           icon=icon)

      try:
        locked = self._params.get_bool(param + "Lock")
      except UnknownKeyName:
        locked = False

      toggle.action_item.set_enabled(not locked)
      if locked:
        self._locked_toggles.add(param)

      # Re-insert into the ordered dict at the desired position
      new_toggles = {}
      for key, value in self._toggles.items():
        new_toggles[key] = value
        if key == after:
          new_toggles[param] = toggle
      self._toggles = new_toggles

    self._scroller = Scroller(list(self._toggles.values()), line_separator=True, spacing=0)
