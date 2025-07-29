#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mesh.h>
#include <shader.h>
#include <stb_image.h>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>

Mesh::Mesh(float *vertices, const std::string &fragPath)
    : _shader("shaders/vertex.glsl", fragPath.c_str())
{
    _vertices = vertices;
}

void Mesh::load()
{
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    _vertexCount = 32;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(float), _vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw()
{

    for (size_t i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + static_cast<int>(i));
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
    }

    _shader.useProgram();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::setTextures(const std::vector<std::string> &texPaths)
{
    _texPaths = texPaths;
}

void Mesh::loadTexture()
{
    if (_texPaths.empty())
        throw std::runtime_error("Textures path not set");

    _textures.resize(_texPaths.size());

    for (size_t i = 0; i < _texPaths.size(); ++i)
    {
        glGenTextures(1, &_textures[i]);
        glBindTexture(GL_TEXTURE_2D, _textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(_texPaths[i].c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            GLenum format = (nrChannels == 4 ? GL_RGBA : GL_RGB);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture: " << _texPaths[i] << std::endl;
        }
        stbi_image_free(data);

        // Define o sampler no shader
        _shader.useProgram();
        std::string texName = "texture" + std::to_string(i);
        _shader.setInt(texName, static_cast<int>(i));
    }
}

void Mesh::dispose()
{
    _shader.deleteProgram();

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}