#include <iostream>

#include "input_pipeline/pipeline.h"
#include "mediators/mock_mediator.h"


int main(int argc, char* argv[])
{
    std::shared_ptr<InputPipeline> pipeline = InputPipeline::make_default_pipeline();
    std::shared_ptr<MockMediator>  mediator = MockMediator::make_mediator(pipeline);
    mediator->render = std::make_shared<RenderFacade>(ContextType::qlfw, WindowSize(800, 600));

    // mediator->render->set_puppet("../resources/puppets/nanosuit/nanosuit.obj");
    mediator->render->set_puppet("../resources/puppets/female/female.obj");

    // resize model to fit screen and rotate it towards camera
    glm::mat4 puppet_normalization;
    puppet_normalization = glm::scale(puppet_normalization, glm::vec3(0.32f, 0.32f, 0.32f));
    puppet_normalization = glm::rotate(puppet_normalization, 1.55f, glm::vec3(0.0f, 1.0f, 0.0f));
    puppet_normalization = glm::translate(puppet_normalization, glm::vec3(0.0f, 0.0f, -0.8f));
    mediator->render->set_puppet_normalization(puppet_normalization);

    mediator->render->init_scene();
    mediator->open_stream();
    while (cv::waitKey(30) < 0)
    {
        mediator->render_pipeline();
    }
    mediator->close_stream();

    return 0;
}