#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/opencv.hpp"
#include "input_source.h"
#include "analyzers/face_detector.h"
#include "analyzers/landmark_detector.h"
#include "analyzers/feature_detector.h"


class InputPipeline
{
public:
    explicit InputPipeline(std::unique_ptr<InputSource> input_stream,
                           std::unique_ptr<FaceDetector> face_detector,
                           std::unique_ptr<LandmarkDetector> landmark_detector);

    void open_stream();
    void close_stream();
    void run_pipeline();    // todo: Make private & friend function of mediator interface
    const cv::Mat& get_frame();

private:
    cv::Mat frame;
    std::unique_ptr<InputSource> in_stream;
    std::unique_ptr<FaceDetector> face_detector;
    std::unique_ptr<LandmarkDetector> landmark_detector;
    FeatureDetector feature_detector;
};


std::shared_ptr<InputPipeline> make_default_input_pipeline();

#endif // CAMERA_H