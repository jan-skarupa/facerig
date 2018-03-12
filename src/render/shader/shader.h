#ifndef FACERIG_SHADER_H
#define FACERIG_SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
    Shader();

    void use();
    void set_uniform(const std::string &name, int value) const;
    void set_uniform(const std::string &name, float value) const;
    void set_uniform(const std::string &name, const glm::vec3 &vec) const;
    void set_uniform(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int ID;
    bool shader_compiled(const unsigned int &shader);
    bool program_linked(const unsigned int &program);
};


#endif //FACERIG_SHADER_H
