#ifndef FACERIG_RENDER_H
#define FACERIG_RENDER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <map>

#include "model.h"
#include "shader.h"


class Render {
public:
    explicit Render(GLFWwindow* window) : m_window(window) {};
    void load_shader(std::string vertex_source_path, std::string fragment_source_path);
    void load_scene(std::string path);
    void load_puppet(std::string path);
    void run();
private:
    GLFWwindow* m_window;
    Shader      m_shader;
    Model       m_scene;
    Model       m_puppet;
};


#endif //FACERIG_RENDER_H
