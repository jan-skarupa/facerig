#ifndef FACERIG_FACE_DETECTOR_HARR_H
#define FACERIG_FACE_DETECTOR_HARR_H

#include "face_detector.h"

class FaceDetectorHarr : public FaceDetector {
public:
    explicit FaceDetectorHarr(const char* detector_source)
    {
        if (!face_classifier.load(detector_source)) {
            std::cout << "Classifier not loaded" << std::endl;
            throw;
        }
    }

    std::vector<cv::Rect> detect_faces(const cv::Mat &frame) override;

private:
    cv::CascadeClassifier face_classifier;
};

#endif //FACERIG_FACE_DETECTOR_HARR_H
