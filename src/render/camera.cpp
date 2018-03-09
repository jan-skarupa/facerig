#include "camera.h"

InputHandler::InputHandler(const glm::vec3 &m_position, const glm::vec3 &m_target, float m_FOV = 45.0f, float m_min_dist = 0.1f, float m_max_dist = 100.0f)
        : m_position(m_position), m_target(m_target), m_FOV_rad(m_FOV), m_min_dist(m_min_dist), m_max_dist(m_max_dist)
{}

void InputHandler::set_position(const glm::vec3 position)
{
    InputHandler::m_position = position;
}

void InputHandler::set_target(const glm::vec3 target)
{
    InputHandler::m_target = target;
}


