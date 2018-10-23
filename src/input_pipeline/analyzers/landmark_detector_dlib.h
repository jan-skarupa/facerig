#ifndef FACERIG_LANDMARK_DETECTOR_DLIB_H
#define FACERIG_LANDMARK_DETECTOR_DLIB_H

#include "landmark_detector.h"


class LandmarkDetectorDlib : public LandmarkDetector {
public:
    explicit LandmarkDetectorDlib(const char *fld_model_path);

    std::array<cv::Point, 68> detect_landmarks(const cv::Mat &frame, const cv::Rect &face) override;

private:
    dlib::shape_predictor fld_model;
    dlib::full_object_detection landmarks;
};

#endif //FACERIG_LANDMARK_DETECTOR_DLIB_H
