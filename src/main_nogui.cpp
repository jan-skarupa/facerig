#include <iostream>

#include "input_pipeline/pipeline.h"
#include "mediators/mock_mediator.h"


int main(int argc, char* argv[])
{
    std::shared_ptr<InputPipeline> pipeline = make_default_input_pipeline();
    std::shared_ptr<MockMediator>  mediator = make_mock_mediator(pipeline);
    mediator->render = std::make_shared<RenderFacade>(ContextType::qlfw, WindowSize(800, 600));

    mediator->render->set_puppet("/home/head/Development/FaceRig/resources/puppets/female/female.obj");
    mediator->render->init_scene();
    mediator->open_stream();
    while (cv::waitKey(30) < 0)
    {
        mediator->render_pipeline();
    }
    mediator->close_stream();

    return 0;
}