#include "selfdrive/ui/qt/widgets/wifi.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

WiFiPromptWidget::WiFiPromptWidget(QWidget *parent) : QFrame(parent) {

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(56, 40, 56, 40);
  main_layout->setSpacing(42);

  QLabel *title = new QLabel(tr("Model Selector"));
  title->setStyleSheet("font-size: 64px; font-weight: 500;");
  main_layout->addWidget(title);

  QLabel *desc = new QLabel(tr("Press to go to the model selector."));
  desc->setStyleSheet("font-size: 40px; font-weight: 400;");
  desc->setWordWrap(true);
  main_layout->addWidget(desc);

  QPushButton *settings_btn = new QPushButton(tr("Models"));
  connect(settings_btn, &QPushButton::clicked, [=]() { emit openSettings(5, "ModelsPanel"); });
  settings_btn->setStyleSheet(R"(
    QPushButton {
      font-size: 48px;
      font-weight: 500;
      border-radius: 10px;
      background-color: #F44336;
      padding: 32px;
    }
    QPushButton:pressed {
      background-color: #D83E33;
    }
  )");
  main_layout->addWidget(settings_btn);

  setStyleSheet(R"(
    WiFiPromptWidget {
      background-color: #333333;
      border-radius: 10px;
    }
  )");
}