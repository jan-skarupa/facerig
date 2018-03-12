#include "render.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void Render::render_scene()
{
    m_shader->use();
    m_shader->set_uniform("view", view);
    m_shader->set_uniform("projection", projection);

    m_shader->set_uniform("light.position", light.position);
    m_shader->set_uniform("light.color", light.color);

    glm::mat4 model;
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    model = glm::rotate(model, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_shader->set_uniform("model", model);

    m_puppet->draw(*m_shader);
}

void Render::set_shader(std::string vertex_source_path, std::string fragment_source_path)
{
    m_shader = std::make_unique<Shader>(vertex_source_path, fragment_source_path);
}

void Render::set_puppet(std::string path)
{
    m_puppet = std::make_unique<Model>(path);
}

void Render::set_light(const Light& light)
{
    Render::light = light;
}

void Render::set_view(const glm::mat4 &view)
{
    Render::view = view;
}

void Render::set_projection(const glm::mat4 &projection)
{
    Render::projection = projection;
}


std::unique_ptr<Render> Render::make_default_render()
{
    std::unique_ptr<Render> render = std::make_unique<Render>();

    glm::mat4 view = glm::lookAt(glm::vec3(2.0, 1.5, 0.0), glm::vec3(0.0, 0.85, 0.0), glm::vec3(0.0, 1.0, 0.0));
    render->set_view(view);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    render->set_projection(projection);

    Light light(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    render->set_light(light);

    render->set_shader("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.glsl");
    render->set_puppet("/home/head/Development/FaceRig/resources/puppets/head/head.obj");

    return std::move(render);
}
