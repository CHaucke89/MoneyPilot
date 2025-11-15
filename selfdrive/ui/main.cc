#include <sys/resource.h>

#include <QApplication>
#include <QTimer>
#include <QTranslator>

#include "selfdrive/ui/frame_streamer.h"
#include "selfdrive/ui/touch_injector.h"
#include "selfdrive/ui/qt/util.h"
#include "selfdrive/ui/qt/window.h"
#include "system/hardware/hw.h"

#ifdef SUNNYPILOT
#include "selfdrive/ui/sunnypilot/qt/window.h"
#define MainWindow MainWindowSP
#else
#include "selfdrive/ui/qt/qt_window.h"
#endif

int main(int argc, char *argv[]) {
  setpriority(PRIO_PROCESS, 0, -20);

  qInstallMessageHandler(swagLogMessageHandler);
  initApp(argc, argv);

  QTranslator translator;
  QString translation_file = QString::fromStdString(Params().get("LanguageSetting"));
  if (!translator.load(QString(":/%1").arg(translation_file)) && translation_file.length()) {
    qCritical() << "Failed to load translation file:" << translation_file;
  }

  QApplication a(argc, argv);
  a.installTranslator(&translator);

  MainWindow w;
  setMainWindow(&w);
  a.installEventFilter(&w);

    // Set up touch injector
  TouchInjector touchInjector(&w);

  // Set up memory-based frame streamer AFTER window is set up
  // Pass the window directly like the working screenshot code did
  QTimer::singleShot(1000, [&w]() {
    // Create frame streamer after window is fully initialized
    static FrameStreamer frameStreamer(&w);
    frameStreamer.start();
    qDebug() << "Frame streaming started after window initialization";
  });

  qDebug() << "UI started with memory-only streaming (no disk storage)";

  return a.exec();
}
