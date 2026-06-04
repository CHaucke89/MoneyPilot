
from openpilot.system.ui.lib.multilang import tr
import pyray as rl
from cereal import custom

from openpilot.system.ui.cloudypilot.lib.styles import style
from openpilot.system.ui.cloudypilot.widgets.toggle import ON_COLOR
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

  def _handle_bundle_download_progress(self):
    super()._handle_bundle_download_progress()

    # Override with cloudypilot ON_COLOR
    labels = {custom.ModelManagerSP.Model.Type.supercombo: self.supercombo_label,
              custom.ModelManagerSP.Model.Type.vision: self.vision_label,
              custom.ModelManagerSP.Model.Type.policy: self.policy_label,
              custom.ModelManagerSP.Model.Type.offPolicy: self.off_policy_label,
              custom.ModelManagerSP.Model.Type.onPolicy: self.on_policy_label}

    if not self.model_manager or (not self.model_manager.selectedBundle and not self.model_manager.activeBundle):
      return

    bundle = self.model_manager.selectedBundle if self._is_downloading() or (
      self.model_manager.selectedBundle and self.model_manager.selectedBundle.status == custom.ModelManagerSP.DownloadStatus.failed
    ) else self.model_manager.activeBundle
    if not bundle:
      return

    for model in bundle.models:
      if label := labels.get(getattr(model.type, 'raw', model.type)):
        p = model.artifact.downloadProgress
        if p.status in (custom.ModelManagerSP.DownloadStatus.downloaded, custom.ModelManagerSP.DownloadStatus.cached):
          label.action_item.color = ON_COLOR
