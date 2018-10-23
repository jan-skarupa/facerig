#include "face_detector_harr.h"

std::vector<cv::Rect> FaceDetectorHarr::detect_faces(const cv::Mat &frame)
{
    std::vector<cv::Rect> faces;
    face_classifier.detectMultiScale(frame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, cv::Size(150, 150));
    return faces;
}
