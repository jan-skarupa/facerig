#ifndef FACERIG_RENDER_FACADE_H
#define FACERIG_RENDER_FACADE_H

#include "render.h"

enum class ContextType { qlfw, qt };


class RenderFacade {
public:
    RenderFacade(ContextType type, WindowSize);
    ~RenderFacade();

    void set_puppet(std::string object_path);
    // void set_puppet_pose(Features features);
    void render_scene();
    void run_glfw_render();

private:
    GLFWwindow* create_glfw_context_window(const WindowSize& window_size);

    int puppet_id;
    GLFWwindow* window;
    std::unique_ptr<Render> render;
};


#endif //FACERIG_RENDER_FACADE_H
