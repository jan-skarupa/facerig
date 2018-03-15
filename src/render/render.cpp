#include "render.h"

#include <glm/gtc/type_ptr.hpp>

unsigned int Render::add_model(std::string object_path)
{
    models.push_back(std::make_unique<Model>(object_path));
    return (unsigned int)models.size()-1;
}

void Render::configure_shaders()
{
    shader.use();
    shader.set_uniform("view", view);
    shader.set_uniform("projection", projection);

    shader.set_uniform("light.position", light.position);
    shader.set_uniform("light.color", light.color);
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

        shader.set_uniform("material." + name + number, (int)i);
        glBindTexture(GL_TEXTURE_2D, textures[used_textures[i]].id);
    }
    glActiveTexture(GL_TEXTURE0);
}

void Render::render_scene()
{
    for (auto &model : models)
    {
        glm::mat4 model_transform = model->transformation;
        for (auto &mesh : model->get_meshes())
        {
            glm::mat4 mesh_transform = model_transform * mesh.transformation;
            shader.set_uniform("model", mesh_transform);

            bind_mesh_textures(model->get_textures(), mesh.get_used_textures());
            glBindVertexArray(mesh.get_vertex_array_id());
            glDrawElements(GL_TRIANGLES, mesh.get_indicies_count(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }
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

glm::mat4 *Render::get_transform_matrix(unsigned int model_id, std::string mesh_name)
{
    if (mesh_name == "") {
        return &(models[model_id]->transformation);
    }

    for (auto &mesh : models[model_id]->get_meshes()) {
        if (mesh.get_name() == mesh_name) {
            return const_cast<glm::mat4*>(&(mesh.transformation));
        }
    }
    return nullptr;
}


std::unique_ptr<Render> Render::make_default_render()
{
    std::unique_ptr<Render> render = std::make_unique<Render>();
    render->set_camera(Camera(glm::vec3(2.0, 1.5, 0.0), glm::vec3(0.0, 0.85, 0.0), WindowSize(800, 600)));
    Light light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    render->set_light(light);

    return std::move(render);
}
