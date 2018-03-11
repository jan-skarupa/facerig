#include <iostream>

#include "pipeline.h"
#include "mediators/mock_mediator.h"

int main(int argc, char* argv[])
{
    std::shared_ptr<InputPipeline> pipeline = make_default_input_pipeline();
    std::shared_ptr<MockMediator>  mediator = make_mock_mediator(pipeline);

    mediator->open_stream();
    while (cv::waitKey(30) < 0)
    {
        mediator->run_pipeline();
    }
    mediator->close_stream();

    return 0;
}