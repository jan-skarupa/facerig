#include <iostream>

#include "render_facade.h"


int main()
{
    std::cout << "Render test..." << std::endl;

    RenderFacade facade(ContextType::qlfw, WindowSize(800, 600));
    facade.set_puppet("/home/head/Development/FaceRig/resources/puppets/nanosuit/nanosuit.obj");
    facade.run_glfw_render();

    return 0;
}
