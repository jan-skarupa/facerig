#include "render.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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

        shader.set_uniform("material." + name + number, (int)i);
        glBindTexture(GL_TEXTURE_2D, textures[used_textures[i]].id);
    }
    glActiveTexture(GL_TEXTURE0);
}

void Render::render_scene()
{
    glm::mat4 transform;
    transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
    transform = glm::rotate(transform, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    shader.set_uniform("model", transform);

    for (auto &model : models)
    {
        for (auto &mesh : model->get_meshes())
        {
            bind_mesh_textures(model->get_textures(), mesh.get_used_textures());
            mesh.draw();
        }
    }
}

void Render::init_scene()
{
    shader.use();
    shader.set_uniform("view", view);
    shader.set_uniform("projection", projection);

    shader.set_uniform("light.position", light.position);
    shader.set_uniform("light.color", light.color);
}

int Render::add_model(std::string object_path)
{
    models.push_back(std::make_unique<Model>(object_path));
    return (int)models.size();
}

void Render::set_light(const Light& light)
{
    Render::light = light;
}

void Render::set_camera(const Camera camera)
{
    glm::mat4 view = glm::lookAt(camera.position, camera.target, glm::vec3(0.0, 1.0, 0.0));
    this->view = view;

    float aspect = (float)camera.window_size.width / (float)camera.window_size.height;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
    this->projection = projection;
}

std::unique_ptr<Render> Render::make_default_render()
{
    std::unique_ptr<Render> render = std::make_unique<Render>();
    render->set_camera(Camera(glm::vec3(2.0, 1.5, 0.0), glm::vec3(0.0, 0.85, 0.0), WindowSize(800, 600)));
    Light light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    render->set_light(light);

    return std::move(render);
}
