#ifndef FACERIG_MODEL_H
#define FACERIG_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "mesh.h"


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};


class Model {
public:
    Model() {};
    explicit Model(std::string & path, glm::mat4 normal)  {
        normalization = normal;
        load_model(path);
    }

    void set_mesh_transformation(unsigned int mesh_id, const glm::mat4 &transform);
    glm::mat4 get_mesh_transformation(unsigned int mesh_id);

    const std::vector<Mesh> &get_meshes() const;
    const std::vector<Texture> &get_textures() const;

    glm::mat4 normalization = glm::mat4(1.0);
    glm::mat4 transformation = glm::mat4(1.0);

private:
    void load_model(std::string path);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Vertex> load_vertices(const aiMesh *mesh);
    std::vector<unsigned int> load_indices(const aiMesh *mesh);

    bool mesh_has_material(const aiMesh *mesh);
    std::vector<unsigned int> load_material(const aiMesh *mesh, const aiScene *scene);
    unsigned int load_texture(aiString image_path, aiTextureType type);

    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures;
};


#endif //FACERIG_MODEL_H
