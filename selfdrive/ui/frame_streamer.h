#ifndef FRAME_STREAMER_H
#define FRAME_STREAMER_H

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QByteArray>
#include <memory>
#include <atomic>

class QWidget;
class QTimer;

class FrameStreamer : public QObject {
  Q_OBJECT

public:
  explicit FrameStreamer(QWidget* window, QObject* parent = nullptr);
  ~FrameStreamer();

  void start();
  void stop();

  // Pack the struct to ensure consistent layout between C++ and Python
  #pragma pack(push, 1)
  struct SharedFrame {
    uint64_t timestamp;
    uint32_t width;
    uint32_t height;
    uint32_t size;
    uint32_t format;
    uint8_t ready;
    uint8_t padding[6];  // Align data to 32-byte boundary
    uint8_t data[4 * 1920 * 1080];  // Max 4K frame buffer
  };
  #pragma pack(pop)

private slots:
  void captureFrame();

private:
  void initSharedMemory();
  void cleanupSharedMemory();

  QWidget* window_;
  QTimer* timer_;
  SharedFrame* shared_frame_;
  int shm_fd_;
  void* shm_ptr_;
  QMutex mutex_;

  static constexpr const char* SHM_NAME = "/openpilot_ui_frames";
  static constexpr size_t SHM_SIZE = sizeof(SharedFrame);
};

#endif // FRAME_STREAMER_H