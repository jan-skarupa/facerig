#include "model.h"

unsigned int texture_from_file(const char *path, std::string & directory);


void Model::load_model(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        throw;
    }
    directory = path.substr(0, path.find_last_of('/'));

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        meshes.emplace_back(process_mesh(scene->mMeshes[i], scene));
    }
}


std::vector<Vertex> Model::load_vertices(const aiMesh *mesh)
{
    std::vector<Vertex> vertices;
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    return vertices;
}

std::vector<unsigned int> Model::load_indices(const aiMesh *mesh)
{
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return indices;
}


bool Model::mesh_has_material(const aiMesh *mesh)
{
    return mesh->mMaterialIndex >= 0;
}

unsigned int Model::load_texture(aiString image_path, aiTextureType type)
{
    for (unsigned int i=0; i<textures.size(); i++) {
        if(std::strcmp(textures[i].path.data(), image_path.C_Str()) == 0) {
            return i;
        }
    }

    Texture texture;
    texture.id = texture_from_file(image_path.C_Str(), directory);
    texture.type = type == aiTextureType_DIFFUSE ? "texture_diffuse" : "texture_specular";
    texture.path = image_path.C_Str();
    textures.push_back(texture);

    return textures.size()-1;
}

std::vector<unsigned int> Model::load_material(const aiMesh *mesh, const aiScene *scene)
{
    std::vector<unsigned int> texture_ids;
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::array<aiTextureType, 2> texture_types = { aiTextureType_DIFFUSE, aiTextureType_SPECULAR };

    for (auto &type : texture_types)
    {
        for(unsigned int i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString image_path;
            material->GetTexture(type, i, &image_path);
            texture_ids.push_back(load_texture(image_path, type));
        }
    }

    return texture_ids;
}


Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
    std::string name = std::string(mesh->mName.C_Str());
    std::cout << name << std::endl;
    std::vector<Vertex> vertices = load_vertices(mesh);
    std::vector<unsigned int> indices = load_indices(mesh);
    std::vector<unsigned int> texture_ids;

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    aiColor3D color(0.f, 0.f, 0.f);
    material->Get(AI_MATKEY_COLOR_DIFFUSE,color);
    glm::vec3 base_color = glm::vec3(color[0], color[1], color[2]);

    if (mesh_has_material(mesh)) {
        texture_ids = load_material(mesh, scene);
    }

    return Mesh(name, vertices, indices, base_color, texture_ids);
}

const std::vector<Mesh> &Model::get_meshes() const
{
    return meshes;
}

const std::vector<Texture> &Model::get_textures() const
{
    return textures;
}

void Model::set_mesh_transformation(unsigned int mesh_id, const glm::mat4 &transform) {
    meshes[mesh_id].transformation = transform;
}

glm::mat4 Model::get_mesh_transformation(const unsigned int mesh_id) {
    return meshes[mesh_id].transformation;
}

unsigned int texture_from_file(const char *path, std::string & directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
