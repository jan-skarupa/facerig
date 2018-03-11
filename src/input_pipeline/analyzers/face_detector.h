#ifndef FACERIG_FACE_LANDMARK_DETECTOR_H
#define FACERIG_FACE_LANDMARK_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>


struct FaceDetector {
    virtual cv::Rect detect_face(const cv::Mat& image) = 0;
};


std::unique_ptr<FaceDetector> make_harr_face_detector(const char* source_filepath);

#endif //FACERIG_FACE_LANDMARK_DETECTOR_H
