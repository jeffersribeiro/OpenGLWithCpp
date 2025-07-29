#ifndef MESH_H
#define MESH_H

#include <shader.h>

class Mesh
{
public:
    Mesh(float vertices[], const std::string &fragPath);

    void draw();
    void load();
    void dispose();
    void loadTexture();

private:
    int _vertexCount;
    unsigned int VAO, VBO, EBO;

    float *_vertices;
    float *_texCords;
    Shader _shader;
    unsigned int texture;
};

#endif