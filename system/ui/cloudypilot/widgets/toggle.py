from collections.abc import Callable

import pyray as rl
from openpilot.system.ui.sunnypilot.widgets.toggle import ToggleSP

ON_COLOR = rl.Color(255, 140, 0, 255)

class ToggleCP(ToggleSP):
  def __init__(self, initial_state=False, callback: Callable[[bool], None] | None = None, param: str | None = None):
    ToggleSP.__init__(self, initial_state, callback)
