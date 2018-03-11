#ifndef FACERIG_FEATURES_DETECTOR_H
#define FACERIG_FEATURES_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <array>
#include <vector>


class FeatureDetector {
public:
    FeatureDetector();

    cv::Mat detect_face_direction(const std::array<cv::Point, 68> &landmarks);

private:
    void extract_landmark_points(const std::array<cv::Point, 68> &landmarks);

    cv::Mat camera_matrix;
    cv::Mat dist_coeffs;
    std::array<cv::Point3d, 6> reference_points;
    std::array<cv::Point2d, 6> image_landmarks;
};


#endif //FACERIG_FEATURES_DETECTOR_H
