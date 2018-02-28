#include "shader.h"


Shader::Shader(std::string vertex_source_path, std::string fragment_source_path)
{
    std::string vertex_code, fragment_code;
    copy_file_content(vertex_source_path, vertex_code);
    copy_file_content(fragment_source_path, fragment_code);
    const char* vertex_c_code = vertex_code.c_str();
    const char* fragment_c_code = fragment_code.c_str();

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_c_code, nullptr);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_c_code, nullptr);
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

bool Shader::copy_file_content(std::string path, std::string &content)
{
    std::ifstream file;
    std::stringstream ss;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);
        ss << file.rdbuf();
        file.close();
        content = ss.str();
    }
    catch(std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        return false;
    }

    return true;
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