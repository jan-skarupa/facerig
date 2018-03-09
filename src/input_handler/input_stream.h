#ifndef FACERIG_INPUT_STREAM_H
#define FACERIG_INPUT_STREAM_H


#include "opencv2/opencv.hpp"

struct cam_resolution {
    cam_resolution(int width, int height) : width(width), height(height) {};
    int width;
    int height;
};

class input_stream {
public:
    virtual void open_stream(int cam_device_id, cam_resolution res = cam_resolution(640, 480)) = 0;
    virtual void close_stream() = 0;
    virtual cv::Mat get_image() = 0;
};

std::unique_ptr<input_stream> make_camera_stream();

#endif //FACERIG_INPUT_STREAM_H
