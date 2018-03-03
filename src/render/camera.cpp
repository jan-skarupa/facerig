#include "camera.h"

Camera::Camera(const glm::vec3 &m_position, const glm::vec3 &m_target, float m_FOV = 45.0f, float m_min_dist = 0.1f, float m_max_dist = 100.0f)
        : m_position(m_position), m_target(m_target), m_FOV_rad(m_FOV), m_min_dist(m_min_dist), m_max_dist(m_max_dist)
{}

void Camera::set_position(const glm::vec3 position)
{
    Camera::m_position = position;
}

void Camera::set_target(const glm::vec3 target)
{
    Camera::m_target = target;
}


