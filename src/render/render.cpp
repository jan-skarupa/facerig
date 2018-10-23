#include "render.h"
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Render::create_glfw_context(WindowSize winsize)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(winsize.width, winsize.height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw;
    }

    glViewport(0, 0, winsize.width, winsize.height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


Render::Render(Camera cam, WindowSize winsize) : camera(cam), window_size(winsize)
{
    create_glfw_context(winsize);

    shader = std::make_unique<Shader>();
    shader->use();
    update_projection_matricies();
}


unsigned int Render::add_model(std::string object_path, glm::mat4 normaliz_mat)
{
    std::cout << object_path << std::endl;
    models.push_back(std::make_unique<Model>(object_path, normaliz_mat));
    return (unsigned int)models.size()-1;
}


void Render::bind_mesh_textures(const std::vector<Texture> &textures, const std::vector<unsigned int> &used_textures)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < used_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[used_textures[i]].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->set_uniform("material." + name + number, (int)i);
        glBindTexture(GL_TEXTURE_2D, textures[used_textures[i]].id);
    }
    glActiveTexture(GL_TEXTURE0);
}


void Render::render_scene()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto &model : models)
    {
        glm::mat4 model_transform = model->normalization * model->transformation;
        for (auto &mesh : model->get_meshes())
        {
            glm::mat4 mesh_transform = model_transform * mesh.transformation;
            // shader->set_uniform("model", mesh_transform);

            shader->set_uniform("model", mesh_transform);
            shader->set_uniform("color", mesh.get_base_color());

            bind_mesh_textures(model->get_textures(), mesh.get_used_textures());
            glBindVertexArray(mesh.get_vertex_array_id());
            glDrawElements(GL_TRIANGLES, mesh.get_indicies_count(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}


void Render::set_light(const Light& new_light)
{
    light = new_light;
    shader->set_uniform("light.position", light.position);
    shader->set_uniform("light.color", light.color);
}

void Render::set_camera(const Camera &cam) {
    camera = cam;
    update_projection_matricies();
}

void Render::update_projection_matricies()
{
    float aspect_ratio = (float)window_size.width / (float)window_size.height;
    view = glm::lookAt(camera.position, camera.target, glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f);

    shader->set_uniform("view", view);
    shader->set_uniform("projection", projection);
}

void Render::set_camera_target(const glm::vec3 &target) {
    camera.target = target;
    update_projection_matricies();
}

void Render::set_camera_position(const glm::vec3 &position) {
    camera.position = position;
    update_projection_matricies();
}

void Render::set_model_transformation(unsigned int model_id, glm::mat4 transformation) {
    models[model_id]->transformation = transformation;
}

void Render::set_mesh_transformation(unsigned int model_id, unsigned int mesh_id, const glm::mat4 &transformation) {
    models[model_id]->set_mesh_transformation(mesh_id, transformation);
}
