#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    Shader(const std::string &vertPath, const std::string &fragPath);

    void useProgram();
    void deleteProgram();
    int getProgram();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

private:
    int ID;
    unsigned int vertexShader;
    unsigned int fragmentShader;
};

#endif