#include <iostream>

#include "render_facade.h"


int main()
{
    glm::mat4 pose, normalization;
    normalization = glm::scale(normalization, glm::vec3(0.10f, 0.10f, 0.10f));
    normalization = glm::rotate(normalization, 1.55f, glm::vec3(0.0f, 1.0f, 0.0f));
    normalization = glm::translate(normalization, glm::vec3(0.0f, 0.0f, -0.8f));

    RenderFacade facade(ContextType::qlfw, WindowSize(800, 600));
    facade.set_puppet("../resources/puppets/nanosuit/nanosuit.obj");
    facade.set_puppet_normalization(normalization);
    facade.set_puppet_pose(pose);

    facade.run_glfw_render();

    return 0;
}
