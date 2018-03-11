#include "feature_detector.h"

void FeatureDetector::extract_landmark_points(const std::array<cv::Point, 68> &landmarks)
{
    image_landmarks[0] = cv::Point2d(landmarks[30]);    // Nose tip
    image_landmarks[1] = cv::Point2d(landmarks[8]);     // Chin
    image_landmarks[2] = cv::Point2d(landmarks[45]);    // Left eye left corner
    image_landmarks[3] = cv::Point2d(landmarks[36]);    // Right eye right corner
    image_landmarks[4] = cv::Point2d(landmarks[54]);    // Left Mouth corner
    image_landmarks[5] = cv::Point2d(landmarks[48]);    // Right mouth corner
}


FeatureDetector::FeatureDetector()
{
    double focal_length = 640; // res.width;1280 720
    // cv::Point2d center = cv::Point2d(res.width / 2, res.height / 2);
    cv::Point2d center = cv::Point2d(640, 360); // 320, 240
    camera_matrix = (cv::Mat_<double>(3, 3) << focal_length, 0, center.x, 0, focal_length, center.y, 0, 0, 1);
    dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type); // Assuming no lens distortion

    reference_points[0] = cv::Point3d(0.0f, 0.0f, 0.0f);           // Nose tip
    reference_points[1] = cv::Point3d(0.0f, -330.0f, -65.0f);      // Chin
    reference_points[2] = cv::Point3d(-225.0f, 170.0f, -135.0f);   // Left eye left corner
    reference_points[3] = cv::Point3d(225.0f, 170.0f, -135.0f);    // Right eye right corner
    reference_points[4] = cv::Point3d(-150.0f, -150.0f, -125.0f);  // Left Mouth corner
    reference_points[5] = cv::Point3d(150.0f, -150.0f, -125.0f);   // Right mouth corner
}

cv::Mat FeatureDetector::detect_face_direction(const std::array<cv::Point, 68> &landmarks)
{
    cv::Mat rotation_vector;
    cv::Mat translation_vector;

    extract_landmark_points(landmarks);
    cv::solvePnP(reference_points, image_landmarks, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

    double vert = rotation_vector.at<double>(0,0);
    double horz = rotation_vector.at<double>(1,0);
    double tilt = rotation_vector.at<double>(2,0);
    std::cout << "horz: " << horz*57 << "; vert: " << vert*57 << std::endl;

    return rotation_vector;
}
