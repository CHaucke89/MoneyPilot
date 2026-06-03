import pyray as rl

from openpilot.selfdrive.ui.sunnypilot.onroad.hud_renderer import HudRendererSP, UI_CONFIG
from openpilot.selfdrive.ui.cloudypilot.onroad.torque_button import TorqueButton


class HudRendererCP(HudRendererSP):
  def __init__(self):
    super().__init__()
    self._torque_button = TorqueButton(UI_CONFIG.button_size, UI_CONFIG.wheel_icon_size)

  def set_torque_settings_callback(self, callback) -> None:
    self._torque_button.set_callback(callback)

  def user_interacting(self) -> bool:
    return super().user_interacting() or self._torque_button.is_pressed

  def _render(self, rect: rl.Rectangle) -> None:
    super()._render(rect)
    button_x = rect.x + rect.width - UI_CONFIG.border_size - UI_CONFIG.button_size
    button_y = rect.y + UI_CONFIG.border_size
    torque_x = button_x - UI_CONFIG.border_size - UI_CONFIG.button_size
    self._torque_button.render(rl.Rectangle(torque_x, button_y, UI_CONFIG.button_size, UI_CONFIG.button_size))
