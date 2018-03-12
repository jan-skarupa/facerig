#include "shader.h"

Shader::Shader()
{
    extern const char* vertex_literal;
    extern const char* fragment_literal;

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_literal, nullptr);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_literal, nullptr);
    glCompileShader(fragmentShader);

    if ( !(shader_compiled(vertexShader) && shader_compiled(fragmentShader)) ) {
        throw; // todo: throw better exception
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!program_linked(ID)) {
        throw;
    }
}

void Shader::use()
{
    glUseProgram(ID);
}

bool Shader::shader_compiled(const unsigned int &shader)
{
    int success;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << log << std::endl;
        return false;
    };
    return true;
}

bool Shader::program_linked(const unsigned int &program)
{
    int success;
    char log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    };
    return true;
}


void Shader::set_uniform(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_uniform(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set_uniform(const std::string &name, const glm::vec3 &vec) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
}

void Shader::set_uniform(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}