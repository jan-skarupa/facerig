#include "mesh.h"

#include <utility>

Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           glm::vec3 base_color, std::vector<unsigned int> texture_ids)
        : name(std::move(name)), vertices(std::move(vertices)), indices(std::move(indices)),
          base_color(base_color), texture_ids(std::move(texture_ids))
{
    load_to_buffers();
}

void Mesh::load_to_buffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

const std::vector<unsigned int> &Mesh::get_used_textures() const
{
    return texture_ids;
}

const std::string &Mesh::get_name() const
{
    return name;
}

unsigned int Mesh::get_vertex_array_id() const
{
    return VAO;
}

unsigned long Mesh::get_indicies_count() const
{
    return indices.size();
}

const glm::vec3 &Mesh::get_base_color() const
{
    return base_color;
}

