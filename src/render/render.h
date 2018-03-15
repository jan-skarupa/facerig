#ifndef FACERIG_RENDER_H
#define FACERIG_RENDER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <map>
#include <memory>
#include <vector>

#include "model/model.h"
#include "shader/shader.h"
#include "camera/camera.h"


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

    unsigned int add_model(std::string object_path);
    void configure_shaders();
    void render_scene();

    void set_light(const Light& light);
    void set_camera(const Camera camera);
    glm::mat4* get_transform_matrix(unsigned int model_id, std::string mesh_name = "");

private:
    void bind_mesh_textures(const std::vector<Texture> &textures, const std::vector<unsigned int> &used_textures);

    glm::mat4 view;
    glm::mat4 projection;
    Light light;

    Shader shader;
    std::vector<std::unique_ptr<Model>> models;
};


#endif //FACERIG_RENDER_H
