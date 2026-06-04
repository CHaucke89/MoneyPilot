import pyray as rl
from collections.abc import Callable
from openpilot.system.ui.sunnypilot.widgets.option_control import OptionControlSP, LABEL_WIDTH
from openpilot.system.ui.lib.application import MousePos



class OptionControlCP(OptionControlSP):
  def __init__(self, param: str, min_value: int, max_value: int,
               value_change_step: int = 1, enabled: bool | Callable[[], bool] = True,
               on_value_changed: Callable[[int], None] | None = None,
               value_map: dict[int, int] | None = None,
               label_width: int = LABEL_WIDTH,
               use_float_scaling: bool = False, label_callback: Callable[[int], str] | None = None,
               reset_enabled: bool = False):

    super().__init__(param, min_value, max_value)
    self._reset_enabled = reset_enabled
    self.label_rect = rl.Rectangle(0, 0, 0, 0)

  def reset_to_default(self):
    default = self.params.get_default_value(self.param_key)
    if default is None:
      return
    if self.value_map:
      for k, v in self.value_map.items():
        if v == default:
          self.set_value(int(k))
          return
    else:
      self.set_value(int(float(default) * 100.0) if self.use_float_scaling else int(default))

  def _handle_mouse_release(self, mouse_pos: MousePos):
    if self._minus_enabled and rl.check_collision_point_rec(mouse_pos, self.minus_btn_rect):
      new_value = self.current_value - self.value_change_step
      new_value = max(self.min_value, new_value)
      self.set_value(new_value)
    elif self._plus_enabled and rl.check_collision_point_rec(mouse_pos, self.plus_btn_rect):
      new_value = self.current_value + self.value_change_step
      new_value = min(self.max_value, new_value)
      self.set_value(new_value)
    elif self._reset_enabled and rl.check_collision_point_rec(mouse_pos, self.label_rect):
      self.reset_to_default()
