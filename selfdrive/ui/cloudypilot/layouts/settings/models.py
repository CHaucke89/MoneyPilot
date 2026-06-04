
import time
import pyray as rl
from openpilot.system.ui.lib.multilang import tr
from cereal import custom
from openpilot.selfdrive.ui.ui_state import device, ui_state

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
    labels = {custom.ModelManagerSP.Model.Type.supercombo: self.supercombo_label,
              custom.ModelManagerSP.Model.Type.vision: self.vision_label,
              custom.ModelManagerSP.Model.Type.policy: self.policy_label,
              custom.ModelManagerSP.Model.Type.offPolicy: self.off_policy_label,
              custom.ModelManagerSP.Model.Type.onPolicy: self.on_policy_label}
    for label in labels.values():
      label.set_visible(False)
    self.cancel_download_item.set_visible(False)

    if not self.model_manager or (not self.model_manager.selectedBundle and not self.model_manager.activeBundle):
      return

    bundle = self.model_manager.selectedBundle if self._is_downloading() or (
      self.model_manager.selectedBundle and self.model_manager.selectedBundle.status == custom.ModelManagerSP.DownloadStatus.failed
    ) else self.model_manager.activeBundle
    if not bundle:
      return

    self.download_status = bundle.status
    status_changed = self.prev_download_status != self.download_status
    self.prev_download_status = self.download_status

    self.cancel_download_item.set_visible(bool(self.model_manager.selectedBundle) and bool(ui_state.params.get("ModelManager_DownloadIndex")))

    if (current_time := time.monotonic()) - self.last_cache_calc_time > 0.5:
      self.last_cache_calc_time = current_time
      self.clear_cache_item.action_item.set_value(f"{self.calculate_cache_size():.2f} MB")

    if self.download_status == custom.ModelManagerSP.DownloadStatus.downloading:
      device._reset_interactive_timeout()

    for model in bundle.models:
      if label := labels.get(getattr(model.type, 'raw', model.type)):
        label.set_visible(True)
        p = model.artifact.downloadProgress
        text, show, color = f"pending - {bundle.displayName}", False, rl.GRAY
        if p.status == custom.ModelManagerSP.DownloadStatus.downloading:
          text, show = f"{int(p.progress)}% - {bundle.displayName}", True
        elif p.status in (custom.ModelManagerSP.DownloadStatus.downloaded, custom.ModelManagerSP.DownloadStatus.cached):
          status_text = tr("from cache" if p.status == custom.ModelManagerSP.DownloadStatus.cached else "downloaded")
          text, color = f"{bundle.displayName} - {status_text if status_changed else tr('ready')}", ON_COLOR
        elif p.status == custom.ModelManagerSP.DownloadStatus.failed:
          text, color = f"download failed - {bundle.displayName}", rl.RED
        label.action_item.update(p.progress, text, show, color)
