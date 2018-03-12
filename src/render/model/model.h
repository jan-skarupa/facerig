#ifndef FACERIG_MODEL_H
#define FACERIG_MODEL_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"

#include "mesh.h"
#include "../shader/shader.h"


class Model {
public:
    Model() {};
    explicit Model(std::string & path)  {
        load_model(path);
    }

    void draw(Shader shader);

private:
    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;

    void load_model(std::string path);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> load_material_textures(aiMaterial *mat, aiTextureType type, std::string typeName);
};


#endif //FACERIG_MODEL_H
