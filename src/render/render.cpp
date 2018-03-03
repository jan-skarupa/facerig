#include "render.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void Render::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window, true);

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_shader->use();
        m_shader->set_uniform("light.position", glm::vec3(2.0f, 2.0f, 2.0f));
        m_shader->set_uniform("light.color", glm::vec3(1.0f, 1.0f, 1.0f));

        glm::mat4 model;
        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        model = glm::rotate(model, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f));
        m_shader->set_uniform("model", model);

        glm::mat4 view = glm::lookAt(glm::vec3(2.0, 1.5, 0.0), glm::vec3(0.0, 0.85, 0.0), glm::vec3(0.0, 1.0, 0.0));
        m_shader->set_uniform("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        m_shader->set_uniform("projection", projection);

        m_puppet->draw(*m_shader);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void Render::set_shader(std::string vertex_source_path, std::string fragment_source_path)
{
    m_shader = std::make_unique<Shader>(vertex_source_path, fragment_source_path);
}

void Render::load_scene(std::string path)
{
    m_scene = std::make_unique<Model>(path);
}

void Render::load_puppet(std::string path)
{
    m_puppet = std::make_unique<Model>(path);
}

void Render::set_camera()
{

}
