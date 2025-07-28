#include <iostream>
#include <glad/glad.h>
#include <mesh.h>
#include <shader.h>

Mesh::Mesh(float *vertices, const std::string &fragPath)
    : _shader("shaders/shader.vert", fragPath.c_str())
{
    _vertices = vertices;
}

void Mesh::load()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices) * sizeof(float), _vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
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
    glDeleteBuffers(2, &VBO);
}