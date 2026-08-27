"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import os
import time

import pyray as rl

from openpilot.common.hardware import HARDWARE
from openpilot.common.params import Params
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.lib.text_measure import measure_text_cached
from openpilot.system.ui.widgets import Widget


class ScreenSaverSP(Widget):
  def __init__(self, params: Params | None = None):
    super().__init__()
    self.set_rect(rl.Rectangle(0, 0, gui_app.width, gui_app.height))
    self._params = params or Params()
    self._is_mici = HARDWARE.get_device_type() == 'mici' or (HARDWARE.get_device_type() == "pc" and os.getenv("BIG") != "1")

    self.x = 0.0
    self.y = -100.0
    self.vy = 70.0 if self._is_mici else 200.0
    self.color = rl.color_from_hsv(30, 1, 1)

    self.text = "cloudypilot"
    self.font_size = 50 if self._is_mici else 100
    self._start_time = None
    self._dismiss = False
    self._screensaver_timeout = 300
    self._needs_new_drop = True

  @property
  def is_active(self) -> bool:
    return self._start_time is not None and not self._dismiss

  @property
  def was_dismissed(self) -> bool:
    return self._dismiss

  def initialize(self):
    self._screensaver_timeout = self._params.get("ScreenSaverTimeout", return_default=True)
    if self._start_time is None:
      self._start_time = time.monotonic()
    self._dismiss = False

  def hide_event(self):
    super().hide_event()
    self._dismiss = False
    self._start_time = None

  def _handle_mouse_release(self, mouse_pos):
    self._dismiss = True
    self._start_time = None
    gui_app.pop_widget()
    return super()._handle_mouse_release(mouse_pos)

  def _update_state(self):
    super()._update_state()

    self.font = gui_app.font(FontWeight.AUDIOWIDE)
    text_size = measure_text_cached(self.font, self.text, self.font_size, 0)
    self.logo_width = text_size.x
    self.logo_height = text_size.y

    if self._start_time and time.monotonic() - self._start_time > self._screensaver_timeout:
      self._dismiss = True
      self._start_time = None

    if self._needs_new_drop:
      max_x = max(int(self.rect.width - self.logo_width), 0)
      self.x = float(rl.get_random_value(0, max_x))
      self.y = -self.logo_height

      hue = rl.get_random_value(20, 40)
      saturation = rl.get_random_value(70, 100) / 100.0
      value = rl.get_random_value(70, 100) / 100.0
      self.color = rl.color_from_hsv(hue, saturation, value)
      self._needs_new_drop = False

    dt = rl.get_frame_time()
    self.y += self.vy * dt

    if self.y > self.rect.height:
      self._needs_new_drop = True

  def _render(self, rect: rl.Rectangle):
    self.set_rect(rect)
    rl.clear_background(rl.BLACK)
    rl.draw_text_ex(self.font, self.text, rl.Vector2(int(self.x), int(self.y)), self.font_size, 0, self.color)
    return -1
