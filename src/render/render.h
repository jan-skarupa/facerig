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

struct WindowSize {
    WindowSize(int width, int height) : width(width), height(height) {};
    int width, height;
};

struct Light {
    Light() {};
    Light(const glm::vec3 &position, const glm::vec3 &color) : position(position), color(color) {};

    glm::vec3 position;
    glm::vec3 color;
};

struct Camera {
    Camera(glm::vec3 position, glm::vec3 target, WindowSize window_size)
            : position(position), target(target), window_size(window_size) {};

    glm::vec3   position;
    glm::vec3   target;
    WindowSize  window_size;
};


class Render {
public:
    Render() {};
    static std::unique_ptr<Render> make_default_render();

    void set_shader(std::string vertex_source_path, std::string fragment_source_path);
    void set_puppet(std::string path);
    // void set_scene(std::string path);

    void set_light(const Light& light);
    void set_view(const glm::mat4 &view);
    void set_projection(const glm::mat4 &projection);

    void render_scene();

private:
    glm::mat4 view;
    glm::mat4 projection;
    Light light;

    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Model>  m_puppet;
    // std::unique_ptr<Model>  m_scene;
};


#endif //FACERIG_RENDER_H
