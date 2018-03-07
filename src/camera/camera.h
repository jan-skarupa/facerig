#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>

#include <QLabel>
#include <QImage>
#include <QPixmap>

#include "opencv2/opencv.hpp"


class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QLabel* cvs, QObject *parent = nullptr);

signals:

public slots:
    void start_camera();
    void stop_camera();
    void get_image();
    void toogle_colormode();

private:
    std::unique_ptr<QTimer> timer;
    std::unique_ptr<cv::VideoCapture> camera_stream;
    char window_name[10] = "CamDebug";
    cv::Mat frame, frame_tmp;
    bool BW_mode = false;

    QLabel* canvas;
};

#endif // CAMERA_H