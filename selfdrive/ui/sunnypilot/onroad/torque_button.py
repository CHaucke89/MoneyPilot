from collections.abc import Callable

import pyray as rl
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.widgets import Widget


class TorqueButton(Widget):
  def __init__(self, button_size: int, icon_size: int):
    super().__init__()
    self._on_click: Callable | None = None
    self._white_color: rl.Color = rl.Color(255, 255, 255, 255)
    self._black_bg: rl.Color = rl.Color(0, 0, 0, 166)
    self._icon: rl.Texture = gui_app.texture('../../selfdrive/assets/icons/menu.png', icon_size, icon_size)
    self._rect = rl.Rectangle(0, 0, button_size, button_size)

  def set_rect(self, rect: rl.Rectangle) -> None:
    self._rect.x, self._rect.y = rect.x, rect.y

  def set_callback(self, callback: Callable) -> None:
    self._on_click = callback

  def _handle_mouse_release(self, _):
    super()._handle_mouse_release(_)
    if self._on_click is not None:
      self._on_click()

  def _render(self, rect: rl.Rectangle) -> None:
    center_x = int(self._rect.x + self._rect.width // 2)
    center_y = int(self._rect.y + self._rect.height // 2)

    self._white_color.a = 180 if self.is_pressed else 255
    rl.draw_circle(center_x, center_y, self._rect.width / 2, self._black_bg)
    rl.draw_texture_ex(self._icon, rl.Vector2(center_x - self._icon.width / 2, center_y - self._icon.height / 2), 0.0, 1.0, self._white_color)
