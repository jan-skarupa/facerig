#ifndef FACERIG_MESH_H
#define FACERIG_MESH_H

#include "glad/glad.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


class Mesh {
public:
    Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> textures);

    unsigned int get_vertex_array_id() const;
    unsigned long get_indicies_count() const;
    const std::string &get_name() const;
    const std::vector<unsigned int> &get_used_textures() const;

    glm::mat4 transformation;

private:
    void load_to_buffers();

    unsigned int VAO, VBO, EBO;
    std::string name;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<unsigned int> texture_ids;
};


#endif //FACERIG_MESH_H
