#include "feature_detector.h"


FeatureDetector::FeatureDetector(const CamResolution &camera_resolution)
{
    camera_matrix = calculate_camera_matrix(camera_resolution);
    dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type); // Assuming no lens distortion

    reference_points[0] = cv::Point3d(0.0f, 0.0f, 0.0f);           // Nose tip
    reference_points[1] = cv::Point3d(0.0f, -330.0f, -65.0f);      // Chin
    reference_points[2] = cv::Point3d(-225.0f, 170.0f, -135.0f);   // Left eye left corner
    reference_points[3] = cv::Point3d(225.0f, 170.0f, -135.0f);    // Right eye right corner
    reference_points[4] = cv::Point3d(-150.0f, -150.0f, -125.0f);  // Left Mouth corner
    reference_points[5] = cv::Point3d(150.0f, -150.0f, -125.0f);   // Right mouth corner
}

std::array<cv::Point2d, 6> FeatureDetector::extract_landmark_points(const std::array<cv::Point, 68> &landmarks)
{
    std::array<cv::Point2d, 6> rigging_landmarks;
    rigging_landmarks[0] = cv::Point2d(landmarks[30]);    // Nose tip
    rigging_landmarks[1] = cv::Point2d(landmarks[8]);     // Chin
    rigging_landmarks[2] = cv::Point2d(landmarks[45]);    // Left eye left corner
    rigging_landmarks[3] = cv::Point2d(landmarks[36]);    // Right eye right corner
    rigging_landmarks[4] = cv::Point2d(landmarks[54]);    // Left Mouth corner
    rigging_landmarks[5] = cv::Point2d(landmarks[48]);    // Right mouth corner

    return rigging_landmarks;
}

std::array<float,3> rotvec_to_eulers(cv::Mat rotation_vector);

std::array<float,3> FeatureDetector::detect_face_direction(const std::array<cv::Point, 68> &landmarks)
{
    cv::Mat rotation_vector;
    cv::Mat translation_vector;

    std::array<cv::Point2d, 6> rigging_landmarks = extract_landmark_points(landmarks);
    cv::solvePnP(reference_points, rigging_landmarks, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

    return rotvec_to_eulers(rotation_vector);
}

cv::Mat FeatureDetector::calculate_camera_matrix(CamResolution camera_resolution)
{
    double focal_length = camera_resolution.width;
    cv::Point2d center = cv::Point2d(camera_resolution.width / 2, camera_resolution.height / 2);
    return (cv::Mat_<double>(3, 3) << focal_length, 0, center.x, 0, focal_length, center.y, 0, 0, 1);
}

std::array<float,3> rotvec_to_eulers(cv::Mat rotation_vector)
{
    cv::Mat rot_mat;
    cv::Rodrigues(rotation_vector, rot_mat);

    double x, y, z;
    double sy = sqrt(rot_mat.at<double>(0,0) * rot_mat.at<double>(0,0) +  rot_mat.at<double>(1,0) * rot_mat.at<double>(1,0) );

    bool singular = sy < 1e-6;

    if (!singular)
    {
        x = atan2(rot_mat.at<double>(2,1) , rot_mat.at<double>(2,2));
        y = atan2(-rot_mat.at<double>(2,0), sy);
        z = atan2(rot_mat.at<double>(1,0), rot_mat.at<double>(0,0));
    }
    else
    {
        x = atan2(-rot_mat.at<double>(1,2), rot_mat.at<double>(1,1));
        y = atan2(-rot_mat.at<double>(2,0), sy);
        z = 0;
    }
    std::array<float,3> arr = {(float)x, (float)y, (float)z};

    return arr;
}