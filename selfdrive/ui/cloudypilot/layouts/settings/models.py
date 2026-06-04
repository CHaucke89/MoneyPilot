
from openpilot.system.ui.lib.multilang import tr

from openpilot.system.ui.cloudypilot.lib.styles import style
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.models import ModelsLayout
from openpilot.system.ui.sunnypilot.widgets.list_view import option_item_sp, LineSeparatorSP


class ModelsLayoutCP(ModelsLayout):
  def _initialize_items(self):
    super()._initialize_items()

    self.camera_offset = option_item_sp(tr("Camera Offset"), "CameraOffset", -35, 35,
                                                  tr("Adjust camera offset to keep vehicle centered."),
                                                  1, None, True, "", style.BUTTON_ACTION_WIDTH, None, True,
                                                  lambda v: f"{v / 100:.2f}m")

    camera_offset_index = next(i for i, item in enumerate(self.items) if item is self.clear_cache_item)
    insert_pos = camera_offset_index + 1

    # Insert camera offset controls directly below clear model cache button
    self.items = self.items[:insert_pos] + [
      LineSeparatorSP(),
      self.camera_offset,
      LineSeparatorSP(),
    ] + self.items[insert_pos:]

    return self.items
