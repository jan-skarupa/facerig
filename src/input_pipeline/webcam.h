#ifndef FACERIG_CAMERA_H
#define FACERIG_CAMERA_H

#include "input_source.h"

class WebCamera : public InputSource {
public:
    void open_stream(int cam_device_id, CamResolution res = CamResolution(640, 480)) override;
    void close_stream() override;
    cv::Mat get_image() override;

private:
    std::unique_ptr<cv::VideoCapture> camera_stream;
};

#endif //FACERIG_CAMERA_H
