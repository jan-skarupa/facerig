#include "camera.h"

InputPipeline::InputPipeline(const glm::vec3 &m_position, const glm::vec3 &m_target, float m_FOV = 45.0f, float m_min_dist = 0.1f, float m_max_dist = 100.0f)
        : m_position(m_position), m_target(m_target), m_FOV_rad(m_FOV), m_min_dist(m_min_dist), m_max_dist(m_max_dist)
{}

void InputPipeline::set_position(const glm::vec3 position)
{
    InputPipeline::m_position = position;
}

void InputPipeline::set_target(const glm::vec3 target)
{
    InputPipeline::m_target = target;
}


