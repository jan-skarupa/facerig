#include "camera.h"

#define FPS 30

Camera::Camera(QLabel* cvs, QObject *parent) : QObject(parent)
{
    timer = std::make_unique<QTimer>(this);
    timer->setInterval(1000/FPS);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(get_image()));
    canvas = cvs;
}

void Camera::get_image()
{
    *camera_stream >> frame;
    cv::flip(frame, frame_tmp, 1);

    if (BW_mode) {
        cv::cvtColor(frame_tmp, frame, cv::COLOR_BGR2GRAY);
        cvtColor(frame, frame_tmp, CV_GRAY2RGB);
        std::swap(frame_tmp, frame);
    } else {
        cvtColor(frame_tmp, frame, CV_BGR2RGB);
    }

    QImage imdisplay((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    canvas->setPixmap(QPixmap::fromImage(imdisplay));
}

void Camera::start_camera()
{
    camera_stream = std::make_unique<cv::VideoCapture>(0);
    camera_stream->set(CV_CAP_PROP_FRAME_WIDTH, 640);
    camera_stream->set(CV_CAP_PROP_FRAME_HEIGHT,480);
    timer->start();
}
void Camera::stop_camera()
{
    timer->stop();
    camera_stream->release();
}

void Camera::toogle_colormode()
{
    BW_mode = !BW_mode;
}
