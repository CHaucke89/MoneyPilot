from openpilot.common.params import Params


class UIStateCP:
  def __init__(self):
    self.params = Params()

    self.use_imperial: bool = False

  def update_params(self) -> None:
    self.use_imperial = self.params.get_bool("UseImperial")

