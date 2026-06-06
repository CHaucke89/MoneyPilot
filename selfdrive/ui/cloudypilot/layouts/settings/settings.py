from openpilot.selfdrive.ui.layouts.settings import settings as OP
from openpilot.selfdrive.ui.cloudypilot.layouts.settings.toggles import TogglesLayoutCP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings import settings as SP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.cruise import CruiseLayout
from openpilot.selfdrive.ui.cloudypilot.layouts.settings.developer import DeveloperLayoutCP
from openpilot.selfdrive.ui.cloudypilot.layouts.settings.device import DeviceLayoutCP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.display import DisplayLayout
from openpilot.selfdrive.ui.cloudypilot.layouts.settings.models import ModelsLayoutCP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.network import NetworkUISP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.osm import OSMLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.settings import SettingsLayoutSP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.software import SoftwareLayoutSP
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.steering import SteeringLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.sunnylink import SunnylinkLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.trips import TripsLayout
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.vehicle import VehicleLayout
from openpilot.selfdrive.ui.cloudypilot.layouts.settings.visuals import VisualsLayoutCP
from openpilot.system.ui.lib.multilang import tr_noop
from openpilot.system.ui.widgets import Widget

PanelInfo = SP.PanelInfo

class SettingsLayoutCP(SettingsLayoutSP):
  def __init__(self):
    super().__init__()
    self._nav_items: list[Widget] = []

    wifi_manager = SP.WifiManager()
    wifi_manager.set_active(False)

    self._panels = {
      OP.PanelType.DEVICE: PanelInfo(tr_noop("Device"), DeviceLayoutCP(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_home.png"),
      OP.PanelType.MODELS: PanelInfo(tr_noop("Models"), ModelsLayoutCP(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_models.png"),
      OP.PanelType.DEVELOPER: PanelInfo(tr_noop("Developer"), DeveloperLayoutCP(), icon="icons/shell.png"),
      OP.PanelType.SOFTWARE: PanelInfo(tr_noop("Software"), SoftwareLayoutSP(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_software.png"),
      OP.PanelType.STEERING: PanelInfo(tr_noop("Steering"), SteeringLayout(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_lateral.png"),
      OP.PanelType.CRUISE: PanelInfo(tr_noop("Cruise"), CruiseLayout(), icon="icons/speed_limit.png"),
      OP.PanelType.NETWORK: PanelInfo(tr_noop("Network"), NetworkUISP(wifi_manager), icon="icons/network.png"),
      OP.PanelType.TOGGLES: PanelInfo(tr_noop("Toggles"), TogglesLayoutCP(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_toggle.png"),
      OP.PanelType.VISUALS: PanelInfo(tr_noop("Visuals"), VisualsLayoutCP(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_visuals.png"),
      OP.PanelType.DISPLAY: PanelInfo(tr_noop("Display"), DisplayLayout(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_display.png"),
      OP.PanelType.OSM: PanelInfo(tr_noop("OSM"), OSMLayout(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_map.png"),
      OP.PanelType.TRIPS: PanelInfo(tr_noop("Trips"), TripsLayout(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_trips.png"),
      OP.PanelType.SUNNYLINK: PanelInfo(tr_noop("sunnylink"), SunnylinkLayout(), icon="icons/wifi_strength_full.png"),
      OP.PanelType.VEHICLE: PanelInfo(tr_noop("Vehicle"), VehicleLayout(), icon="../../sunnypilot/selfdrive/assets/offroad/icon_vehicle.png"),
    }
