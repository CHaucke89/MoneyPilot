from openpilot.common.params import Params
from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.widgets.scroller_tici import Scroller
from openpilot.system.ui.lib.multilang import tr, tr_noop
from openpilot.system.ui.sunnypilot.widgets.list_view import toggle_item_sp


class SafetyLayout(Widget):
  def __init__(self):
    super().__init__()
    self._params = Params()

    # param, title, desc, icon, needs_restart
    self._toggle_defs = {
      "AlwaysOffDM": (
        lambda: tr("Always-Off Driver Monitoring"),
        tr_noop("Disable driver monitoring even when cloudypilot is engaged."),
        "monitoring.png",
        False,
      ),
      "PermaLatch": (
        lambda: tr("Permanent Seatbelt Latch"),
        tr_noop("Allows engaging while the driver's seatbelt is unlatched."),
        "seatbelt.png",
        False,
      ),
    }

    self._toggles = {}
    items = self._initialize_items()
    self._scroller = Scroller(items, line_separator=True, spacing=0)

  def _initialize_items(self):
    items = []
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
      items.append(toggle)
    return items

  def _toggle_callback(self, state: bool, param: str):
    self._params.put_bool(param, state)
    # Mutual exclusion to keep DM out of superposition if both are toggled on
    if param == "AlwaysOffDM" and state:
      self._params.put_bool("AlwaysOnDM", False)
      if "AlwaysOnDM" in self._toggles:
        self._toggles["AlwaysOnDM"].action_item.set_state(False)

  def _render(self, rect):
    self._scroller.render(rect)

  def show_event(self):
    self._scroller.show_event()
