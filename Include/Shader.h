#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>

#include "Color.h"

struct ShaderSource {
    std::string Vertex;
    std::string Fragment;
};

class Shader {
private:
    std::string _filePath;
    unsigned int _rendererID;

    std::unordered_map<std::string, int> _uniformLocationCache;

    int GetUniformLocation(const std::string& name);
    
    ShaderSource ParseShader();
    unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource);
    unsigned int CompileShader(unsigned int type, const std::string& source);
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void UnBind() const;

    // Set uniforms
    void SetUniform4i(const std::string& name, int value);
    void SetUniformColor(const std::string& name, Color color);
    void SetUniform4f(const std::string& name, const glm::vec4& val);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};


#endif /* SHADER_H */