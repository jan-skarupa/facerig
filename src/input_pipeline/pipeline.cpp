#include "pipeline.h"


InputPipeline::InputPipeline(std::unique_ptr<InputSource> input_stream,
                             std::unique_ptr<FaceDetector> face_detector,
                             std::unique_ptr<LandmarkDetector> landmark_detector)
{
    this->in_stream = std::move(input_stream);
    this->face_detector = std::move(face_detector);
    this->landmark_detector = std::move(landmark_detector);
}

void InputPipeline::run_pipeline()
{
    frame = in_stream->get_image();
    cv::Rect face = face_detector->detect_face(frame);

    if (face.area()) {
        std::array<cv::Point, 68> landmarks = landmark_detector->detect_landmarks(frame, face);

        for (const auto &landmark : landmarks) {
            cv::circle(frame, landmark, 1, cv::Scalar(255,0,0), -1);
        }
    }
    cv::rectangle(frame, face, cv::Scalar(0,0,255));
}

void InputPipeline::open_stream()
{
    in_stream->open_stream(0);
}

void InputPipeline::close_stream()
{
    in_stream->close_stream();
}

const cv::Mat& InputPipeline::get_frame()
{
    return frame;
}


std::shared_ptr<InputPipeline> make_default_input_pipeline()
{
    auto in_stream = make_camera_stream();
    auto face_detector = make_harr_face_detector("../resources/face_detection/haarcascade_frontalface_alt.xml");
    auto landmark_detector = make_dlib_landmark_detector("../resources/face_detection/shape_predictor_68_face_landmarks.dat");

    return std::make_shared<InputPipeline>(std::move(in_stream),
                                           std::move(face_detector), std::move(landmark_detector));
}
