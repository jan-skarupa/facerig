#ifndef FACERIG_INPUT_STREAM_H
#define FACERIG_INPUT_STREAM_H

#include "opencv2/opencv.hpp"
#include "camera_resolution.h"

struct InputSource {
    virtual void open_stream(int cam_device_id, CamResolution res = CamResolution(640, 480)) = 0;
    virtual void close_stream() = 0;
    virtual cv::Mat get_image() = 0;
};

std::unique_ptr<InputSource> make_camera_stream();

#endif //FACERIG_INPUT_STREAM_H
