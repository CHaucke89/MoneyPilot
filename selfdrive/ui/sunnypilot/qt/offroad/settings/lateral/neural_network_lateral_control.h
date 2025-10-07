/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include <map>

#include "selfdrive/ui/sunnypilot/ui.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/sunnypilot/qt/offroad/settings/settings.h"

class NeuralNetworkLateralControl : public ParamControl {
  Q_OBJECT

public:
  NeuralNetworkLateralControl();

public slots:
  void updateToggle(bool _offroad);

private:
  Params params;
  bool offroad;

  // Status messages
  const QString STATUS_NOT_AVAILABLE = tr("NNLC is currently not available on this platform.");
  const QString STATUS_CHECK_COMPATIBILITY = tr("Start the car to check car compatibility");
  const QString STATUS_NOT_LOADED = tr("NNLC Not Loaded");
  const QString STATUS_LOADED = tr("NNLC Loaded");
  const QString STATUS_MATCH = tr("Match");
  const QString STATUS_MATCH_EXACT = tr("Exact");
  const QString STATUS_MATCH_FUZZY = tr("Fuzzy");

  // Explanations
  const QString EXPLANATION_FEATURE = tr("Use NNFF rather than the stock torque controller.");

  QString nnffDescriptionBuilder(const QString &custom_description) const {
    return "<b>" + custom_description + "</b><br><br>" + getBaseDescription();
  }

  QString getBaseDescription() const {
    return EXPLANATION_FEATURE + "<br><br>";
  }
};
