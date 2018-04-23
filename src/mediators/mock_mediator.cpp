#include "mock_mediator.h"

void MockMediator::run_pipeline()
{
    input_pipeline.lock()->run_pipeline();
    render_pipeline_output();
}

void MockMediator::render_pipeline()
{
    input_pipeline.lock()->run_pipeline();
    render_pipeline_output();
}

void MockMediator::render_pipeline_output()
{
    cv::Mat image = input_pipeline.lock()->get_frame();
    cv::imshow("Pipeline Output", image);

    glm::mat4 matrix;
    std::array<float,3> rotations = input_pipeline.lock()->head_rotation;
    matrix = glm::rotate(matrix, -rotations[0], glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, -rotations[1], glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, -rotations[2], glm::vec3(1.0f, 0.0f, 0.0f));

    render->set_puppet_pose(matrix);
    render->render_scene();
}


std::shared_ptr<MockMediator> MockMediator::make_mediator(std::shared_ptr<InputPipeline> input_pipeline)
{
    return std::make_shared<MockMediator>(input_pipeline);
}
