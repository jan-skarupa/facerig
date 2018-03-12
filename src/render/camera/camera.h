#ifndef FACERIG_CAMERA_H
#define FACERIG_CAMERA_H

#include <glm/vec3.hpp>


class InputPipeline {
public:
    InputPipeline(const glm::vec3 &m_position, const glm::vec3 &m_target, float m_FOV, float m_min_dist, float m_max_dist);

    void set_position(glm::vec3 position);
    void set_target(glm::vec3 target);

private:
    glm::vec3   m_position;
    glm::vec3   m_target;
    float       m_FOV_rad;
    float       m_min_dist, m_max_dist;

};


#endif //FACERIG_CAMERA_H
