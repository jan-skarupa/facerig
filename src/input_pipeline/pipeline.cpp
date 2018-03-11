#include "pipeline.h"


struct Image {
    cv::Mat frame;
    std::unique_ptr<cv::Rect> face;
    std::array<cv::Point, 68> landmarks;
    cv::Mat head_rotation;
};


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
    Image image;
    image.frame = in_stream->get_image();
    image.face = face_detector->detect_face(image.frame);

    if (image.face != nullptr) {
        image.landmarks = landmark_detector->detect_landmarks(image.frame, *image.face);
        image.head_rotation = feature_detector.detect_face_direction(image.landmarks);

        cv::rectangle(image.frame, *image.face, cv::Scalar(0,0,0));
        for (const auto &mark : image.landmarks) {
            cv::circle(image.frame, mark, 1, cv::Scalar(255,0,0), -1);
        }
    }

    std::swap(image.frame, frame);
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
