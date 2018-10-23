
#include "landmark_detector_dlib.h"

LandmarkDetectorDlib::LandmarkDetectorDlib(const char *fld_model_path)
{
    dlib::deserialize(fld_model_path) >> fld_model;
}

std::array<cv::Point, 68> LandmarkDetectorDlib::detect_landmarks(const cv::Mat &frame, const cv::Rect &face)
{
    cv::Mat img_grey;
    cv::cvtColor(frame, img_grey, CV_BGR2GRAY);
    dlib::cv_image<unsigned char> img(img_grey);

    dlib::rectangle face_region = dlib::rectangle(face.x, face.y, face.x+face.width, face.y+face.height);
    landmarks = fld_model(img, face_region);

    std::array<cv::Point, 68> cv_landmarks;
    for(int i = 0; i < 68; i++) {
        cv_landmarks[i] = cv::Point(landmarks.part(i).x(), landmarks.part(i).y());
    }

    return cv_landmarks;
}
