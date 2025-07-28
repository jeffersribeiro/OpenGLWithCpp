#ifndef MESH_H
#define MESH_H

#include <shader.h>

class Mesh
{
public:
    Mesh(float vetices[9], const std::string &fragPath);

    void draw();
    void load();
    void dispose();

private:
    unsigned int VAO, VBO;
    float *_vertices;
    Shader _shader;
};

#endif