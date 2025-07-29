#ifndef MESH_H
#define MESH_H

#include <shader.h>
#include <vector>
#include <string>

class Mesh
{
public:
    Mesh(float vertices[], const std::string &fragPath);

    void draw();
    void load();
    void dispose();
    void setTextures(const std::vector<std::string> &texPaths);
    void loadTexture();

private:
    int _vertexCount;
    unsigned int VAO, VBO, EBO;

    float *_vertices;
    float *_texCords;
    Shader _shader;
    std::vector<unsigned int> _textures;
    std::vector<std::string> _texPaths;
};

#endif