#include <iostream>

#include "pipeline.h"

int main(int argc, char* argv[])
{
    std::shared_ptr<InputPipeline> pipeline = InputPipeline::make_default_pipeline();

    pipeline->open_stream();
    while (cv::waitKey(30) < 0)
    {
        pipeline->run_pipeline();
        cv::Mat image = pipeline->get_frame();
        cv::imshow("Pipeline Output", image);
    }
    pipeline->close_stream();

    return 0;
}