#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mesh.h>
#include <shader.h>
#include <cmath>

Mesh::Mesh(float *vertices, const std::string &fragPath)
    : _shader("shaders/vertex.glsl", fragPath.c_str())
{
    _vertices = vertices;
}

void Mesh::load()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    _vertexCount = 18;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(float), _vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw()
{
    _shader.useProgram();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Mesh::dispose()
{
    _shader.deleteProgram();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}