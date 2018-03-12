#include "mock_mediator.h"

void MockMediator::run_pipeline()
{
    input_pipeline.lock()->run_pipeline();
    render_pipeline_output();
}

void MockMediator::render_pipeline_output()
{
    cv::Mat image = input_pipeline.lock()->get_frame();
    cv::imshow("Pipeline Output", image);
}


std::shared_ptr<MockMediator> make_mock_mediator(std::shared_ptr<InputPipeline> input_pipeline)
{
    return std::make_shared<MockMediator>(input_pipeline);
}
