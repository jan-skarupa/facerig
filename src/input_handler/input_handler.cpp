#include "input_handler.h"

#define FPS 30

InputHandler::InputHandler(QLabel* canvas, std::unique_ptr<input_stream> in_stream,
                           std::unique_ptr<FaceDetector> face_detector, QObject *parent)
        : QObject(parent), canvas(canvas), in_stream(std::move(in_stream)), face_detector(std::move(face_detector))
{
    timer = std::make_unique<QTimer>(this);
    timer->setInterval(1000/FPS);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(run_instream_pipeline()));
}

void InputHandler::run_instream_pipeline()
{
    cv::Mat frame = in_stream->get_image();

    cv::Rect face = face_detector->detect_face(frame);
    cv::rectangle(frame, face, cv::Scalar(0,0,255));

    QImage imdisplay((uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    canvas->setPixmap(QPixmap::fromImage(imdisplay));
}

void InputHandler::open_stream()
{
    in_stream->open_stream(0);
    timer->start();
}
void InputHandler::close_stream()
{
    timer->stop();
    in_stream->close_stream();
}
