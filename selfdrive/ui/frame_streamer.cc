#include "frame_streamer.h"
#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QBuffer>
#include <QDateTime>
#include <QDebug>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

FrameStreamer::FrameStreamer(QWidget* window, QObject* parent)
    : QObject(parent), window_(window), timer_(nullptr),
      shared_frame_(nullptr), shm_fd_(-1), shm_ptr_(nullptr) {
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &FrameStreamer::captureFrame);
  initSharedMemory();
}

FrameStreamer::~FrameStreamer() {
  stop();
  cleanupSharedMemory();
}

void FrameStreamer::initSharedMemory() {
  // Remove any existing shared memory
  shm_unlink(SHM_NAME);

  // Create shared memory
  shm_fd_ = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (shm_fd_ == -1) {
    qCritical() << "Failed to create shared memory";
    return;
  }

  // Set size
  if (ftruncate(shm_fd_, SHM_SIZE) == -1) {
    qCritical() << "Failed to set shared memory size";
    close(shm_fd_);
    shm_fd_ = -1;
    return;
  }

  // Map memory
  shm_ptr_ = mmap(nullptr, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
  if (shm_ptr_ == MAP_FAILED) {
    qCritical() << "Failed to map shared memory";
    close(shm_fd_);
    shm_fd_ = -1;
    shm_ptr_ = nullptr;
    return;
  }

  // Initialize the shared frame structure
  shared_frame_ = static_cast<SharedFrame*>(shm_ptr_);
  new (shared_frame_) SharedFrame();

  qDebug() << "Shared memory initialized at" << SHM_NAME;
}

void FrameStreamer::cleanupSharedMemory() {
  if (shm_ptr_ && shm_ptr_ != MAP_FAILED) {
    munmap(shm_ptr_, SHM_SIZE);
  }
  if (shm_fd_ != -1) {
    close(shm_fd_);
  }
  shm_unlink(SHM_NAME);
}

void FrameStreamer::start() {
  if (!timer_ || !shared_frame_) return;
  timer_->start(100);  // 10 FPS for better responsiveness
  qDebug() << "Frame streaming started at 10 FPS";
}

void FrameStreamer::stop() {
  if (timer_) {
    timer_->stop();
  }
  qDebug() << "Frame streaming stopped";
}

void FrameStreamer::captureFrame() {
  if (!window_ || !shared_frame_) return;

  QMutexLocker locker(&mutex_);

  // Capture the window - using exact same method as working screenshot code
  QPixmap pixmap = window_->grab();  // This should capture the MainWindow content
  if (pixmap.isNull()) {
    qWarning() << "Failed to capture frame - pixmap is null";
    return;
  }

  // Debug: Check if pixmap has actual content
  if (pixmap.width() == 0 || pixmap.height() == 0) {
    qWarning() << "Captured pixmap has zero dimensions";
    return;
  }

  // Extra debug: Save first frame to file to verify content
  static bool first_frame_saved = false;
  if (!first_frame_saved) {
    QString debug_file = "/tmp/debug_frame.png";
    if (pixmap.save(debug_file)) {
      qDebug() << "Debug: First frame saved to" << debug_file << "- check if it has UI content";
    }
    first_frame_saved = true;
  }

  // Convert to JPEG for compression
  QByteArray jpeg_data;
  QBuffer buffer(&jpeg_data);
  buffer.open(QIODevice::WriteOnly);

  // Save as JPEG with 85% quality (good balance of quality vs size)
  if (!pixmap.save(&buffer, "JPEG", 85)) {
    qWarning() << "Failed to encode frame as JPEG";
    return;
  }

  // Check size
  if (jpeg_data.size() > static_cast<int>(sizeof(shared_frame_->data))) {
    qWarning() << "Frame too large:" << jpeg_data.size() << "bytes";
    return;
  }

  // Mark as not ready while updating
  shared_frame_->ready = 0;

  // Update metadata
  shared_frame_->timestamp = QDateTime::currentMSecsSinceEpoch();
  shared_frame_->width = pixmap.width();
  shared_frame_->height = pixmap.height();
  shared_frame_->size = jpeg_data.size();
  shared_frame_->format = 1;  // 1 = JPEG

  // Copy data
  memcpy(shared_frame_->data, jpeg_data.data(), jpeg_data.size());

  // Memory barrier to ensure all writes are visible
  __sync_synchronize();

  // Mark as ready
  shared_frame_->ready = 1;

  static int frame_count = 0;
  frame_count++;
  if (frame_count % 10 == 0) {  // Log every 10th frame
    qDebug() << "Frame" << frame_count << "captured:" << jpeg_data.size() << "bytes, "
             << pixmap.width() << "x" << pixmap.height()
             << "Window:" << window_->geometry()
             << "Visible:" << window_->isVisible();
  }
}