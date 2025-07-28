#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    Shader(const std::string &vertPath, const std::string &fragPath);

    void useProgram();
    void deleteProgram();

private:
    int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;
};

#endif