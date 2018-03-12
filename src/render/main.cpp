#include <iostream>

#include "render_facade.h"


int main()
{
    std::cout << "Render test..." << std::endl;

    RenderFacade facade(ContextType::qlfw, WindowSize(800, 600));
    facade.run_render();

    return 0;
}
