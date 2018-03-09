#include "input_handler.h"

#define FPS 30

InputHandler::InputHandler(QLabel* canvas, std::unique_ptr<input_stream> in_stream, QObject *parent)
        : QObject(parent), canvas(canvas), in_stream(std::move(in_stream))
{
    timer = std::make_unique<QTimer>(this);
    timer->setInterval(1000/FPS);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(get_image()));
}

void InputHandler::get_image()
{
    cv::Mat frame = in_stream->get_image();
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
