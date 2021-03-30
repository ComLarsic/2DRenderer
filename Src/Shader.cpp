#include "../Include/Renderer.h"
#include "../Include/Shader.h"

Shader::Shader(const std::string& filepath) : _filePath(filepath) {
    ShaderSource source = ParseShader();
    _rendererID = CreateShader(source.Vertex, source.Fragment);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(_rendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(_rendererID));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

/* ------------------- Uniform handling ------------------- */
void Shader::SetUniformColor(const std::string& name, Color color) {
    GLCall(glUniform4f(GetUniformLocation(name), color.R / 255, color.G / 255, color.B / 255, color.A / 255));
}

void Shader::SetUniform4i(const std::string& name, int value) {
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, const glm::vec4& val) {
     GLCall(glUniform4f(GetUniformLocation(name), val.x, val.y, val.z, val.w));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int Shader::GetUniformLocation(const std::string& name) {
    // Check for cached location
    if(_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];

    GLCall( int location = glGetUniformLocation(_rendererID, name.c_str()));

    if (location == -1)
        WARN("Uniform " << name << " does not exist");
    else
        _uniformLocationCache[name] = location;
    
    return location;
}

// Parse a shader file
ShaderSource Shader::ParseShader() {
    auto stream = std::ifstream(_filePath);
    
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        // Handle #shader tags
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            continue;
        }

        ss[int(type)] << line << "\n";
    }

    return { ss[0].str(), ss[1].str() };
}

// Compile a shader source
unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    // Handle compile errors
    if (!result) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char message[length];
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        
        ERROR("Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader: ");
        
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

// Create a shader and shader-program
unsigned int Shader::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int program = glCreateProgram();
    unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    GLCall(glAttachShader(program, vertex));
    GLCall(glAttachShader(program, fragment));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));

    return program;
}
