#ifndef FACERIG_RENDER_FACADE_H
#define FACERIG_RENDER_FACADE_H

#include "render.h"

enum class ContextType { qlfw, qt };


class RenderFacade {
public:
    RenderFacade(ContextType type, WindowSize);
    ~RenderFacade();

    void run_render();
    void render_scene();

private:
    GLFWwindow* create_glfw_context_window(const WindowSize& window_size);

    GLFWwindow* window;
    std::unique_ptr<Render> render;
};


#endif //FACERIG_RENDER_FACADE_H
