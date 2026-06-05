from collections.abc import Callable

from openpilot.system.ui.sunnypilot.widgets.list_view import ListItemSP
from openpilot.system.ui.sunnypilot.widgets.option_control import LABEL_WIDTH
from openpilot.system.ui.cloudypilot.widgets.option_control import OptionControlCP


def option_item_cp(title: str | Callable[[], str], param: str,
                   min_value: int, max_value: int, description: str | Callable[[], str] | None = None,
                   value_change_step: int = 1, on_value_changed: Callable[[int], None] | None = None,
                   enabled: bool | Callable[[], bool] = True,
                   icon: str = "", label_width: int = LABEL_WIDTH, value_map: dict[int, int] | None = None,
                   use_float_scaling: bool = False, label_callback: Callable[[int], str] | None = None,
                   inline: bool = False, reset_enabled: bool = False) -> ListItemSP:
  action = OptionControlCP(
    param, min_value, max_value, value_change_step,
    enabled, on_value_changed, value_map, label_width, use_float_scaling, label_callback, reset_enabled,
  )
  return ListItemSP(title=title, description=description, action_item=action, icon=icon, inline=inline)
