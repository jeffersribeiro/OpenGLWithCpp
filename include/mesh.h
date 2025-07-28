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

private:
    int _vertexCount;
    unsigned int VAO, VBO;
    float *_vertices;
    Shader _shader;
};

#endif