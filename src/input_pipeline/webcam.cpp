
#include "webcam.h"

void WebCamera::open_stream(int cam_device_id, CamResolution res)
{
    camera_stream = std::make_unique<cv::VideoCapture>(cam_device_id);
    camera_stream->set(CV_CAP_PROP_FRAME_WIDTH, res.width);
    camera_stream->set(CV_CAP_PROP_FRAME_HEIGHT,res.height);
}

void WebCamera::close_stream()
{
    camera_stream->release();
}

cv::Mat WebCamera::get_image()
{
    cv::Mat frame;
    *camera_stream >> frame;
    cv::flip(frame, frame, 1);
    return frame;
}