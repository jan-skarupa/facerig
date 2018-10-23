#ifndef FACERIG_RENDER_H
#define FACERIG_RENDER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <map>
#include <memory>
#include <vector>

#include "model/model.h"
#include "shader/shader.h"
#include "../input_pipeline/camera_resolution.h"


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
    Camera(glm::vec3 position, glm::vec3 target) : position(position), target(target) {};

    glm::vec3   position;
    glm::vec3   target;
};


class Render {
public:
    Render(Camera cam, WindowSize winsize);

    unsigned int add_model(std::string object_path, glm::mat4 normaliz_mat = glm::mat4(1.0));
    void render_scene();

    void set_camera(const Camera &cam);
    void set_camera_target(const glm::vec3 &target);
    void set_camera_position(const glm::vec3 &position);
    void set_light(const Light &light);
    void set_model_transformation(unsigned int model_id, glm::mat4 transformation);
    void set_mesh_transformation(unsigned int model_id, unsigned int mesh_id, const glm::mat4 &transformation);

    GLFWwindow* window;

private:
    void update_projection_matricies();
    void create_glfw_context(WindowSize winsize);
    void bind_mesh_textures(const std::vector<Texture> &textures, const std::vector<unsigned int> &used_textures);

    glm::mat4   view;
    glm::mat4   projection;
    WindowSize  window_size;
    Camera      camera;
    Light       light;

    std::unique_ptr<Shader> shader;
    std::vector<std::unique_ptr<Model>> models;
};


#endif //FACERIG_RENDER_H
