#ifndef FACERIG_RENDER_FACADE_H
#define FACERIG_RENDER_FACADE_H

#include "render.h"

enum class ContextType { qlfw, qt };
enum class PuppetParts { head, left_eye, right_eye, jaw };


class RenderFacade {
public:
    RenderFacade(ContextType type, WindowSize);
    ~RenderFacade();

    void set_puppet(std::string object_path);
    void render_scene();
    void run_glfw_render();

private:
    GLFWwindow* create_glfw_context_window(const WindowSize& window_size);

    GLFWwindow* window;
    std::unique_ptr<Render> render;

    unsigned int puppet_id;
    std::map<PuppetParts, glm::mat4*> puppet_transforms;
};


#endif //FACERIG_RENDER_FACADE_H
