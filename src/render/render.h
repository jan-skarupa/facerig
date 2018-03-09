#ifndef FACERIG_RENDER_H
#define FACERIG_RENDER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <map>
#include <memory>
#include <vector>

#include "shader.h"
#include "model.h"
#include "camera.h"


class Render {
public:
    explicit Render(GLFWwindow* window) : m_window(window) {};

    void set_shader(std::string vertex_source_path, std::string fragment_source_path);
    void set_camera();
    void load_scene(std::string path);
    void load_puppet(std::string path);

    void run();

private:
    GLFWwindow* m_window;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<InputHandler> m_camera;
    std::unique_ptr<Model>  m_scene;
    std::unique_ptr<Model>  m_puppet;
};


#endif //FACERIG_RENDER_H
