#include "input_handler.h"

#define FPS 30

InputHandler::InputHandler(QLabel* canvas, std::unique_ptr<input_stream> in_stream,
                           std::unique_ptr<FaceDetector> face_detector,
                           std::unique_ptr<LandmarkDetector> landmark_detector, QObject *parent)
{
    this->canvas = canvas;
    this->in_stream = std::move(in_stream);
    this->face_detector = std::move(face_detector);
    this->landmark_detector = std::move(landmark_detector);

    timer = std::make_unique<QTimer>(this);
    timer->setInterval(1000/FPS);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(run_instream_pipeline()));
}

void InputHandler::run_instream_pipeline()
{
    cv::Mat frame = in_stream->get_image();
    cv::Rect face = face_detector->detect_face(frame);

    if (face.area()) {
        std::array<cv::Point, 68> landmarks = landmark_detector->detect_landmarks(frame, face);

        for (const auto &landmark : landmarks) {
            cv::circle(frame, landmark, 1, cv::Scalar(255,0,0), -1);
        }
    }
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
