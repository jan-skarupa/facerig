#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include <QImage>
#include <QPixmap>

#include "opencv2/opencv.hpp"
#include "input_stream.h"
#include "face_detector.h"
#include "landmark_detector.h"


class InputHandler : public QObject
{
    Q_OBJECT
public:
    explicit InputHandler(QLabel* canvas, std::unique_ptr<input_stream> in_stream,
                          std::unique_ptr<FaceDetector> face_detector,
                          std::unique_ptr<LandmarkDetector> landmark_detector, QObject *parent = nullptr);

public slots:
    void open_stream();
    void close_stream();
    void run_instream_pipeline();

private:
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<input_stream> in_stream;
    std::unique_ptr<FaceDetector> face_detector;
    std::unique_ptr<LandmarkDetector> landmark_detector;
    QLabel* canvas;
};

#endif // CAMERA_H