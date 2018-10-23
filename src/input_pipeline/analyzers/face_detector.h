#ifndef FACERIG_FACE_LANDMARK_DETECTOR_H
#define FACERIG_FACE_LANDMARK_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

struct FaceDetector {
    virtual std::vector<cv::Rect> detect_faces(const cv::Mat &image) = 0;

    cv::Rect find_tracked_face(const std::vector<cv::Rect> &faces, const cv::Rect &tracked_face_prev_loc) {
        return faces[0];
    }
};

#endif //FACERIG_FACE_LANDMARK_DETECTOR_H
