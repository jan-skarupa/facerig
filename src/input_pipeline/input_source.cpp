#include "input_source.h"


class Camera : public InputSource {
public:
    void open_stream(int cam_device_id, CamResolution res) override;
    void close_stream() override;
    cv::Mat get_image() override;

private:
    std::unique_ptr<cv::VideoCapture> camera_stream;
};


void Camera::open_stream(int cam_device_id, CamResolution res = CamResolution(640, 480))
{
    camera_stream = std::make_unique<cv::VideoCapture>(cam_device_id);
    camera_stream->set(CV_CAP_PROP_FRAME_WIDTH, res.width);
    camera_stream->set(CV_CAP_PROP_FRAME_HEIGHT,res.height);
}

void Camera::close_stream()
{
    camera_stream->release();
}

cv::Mat Camera::get_image()
{
    cv::Mat frame;
    *camera_stream >> frame;
    cv::flip(frame, frame, 1);

    return frame;
}


std::unique_ptr<InputSource> make_camera_stream()
{
    return std::make_unique<Camera>();
}
