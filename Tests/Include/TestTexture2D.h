#ifndef TEST_TEXTURE_2D_H
#define TEST_TEXTURE_2D_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "../../Include/Log.h"
#include "../../Include/Renderer.h"
#include "../../Include/Texture.h"

#include "../../Vendor/imgui/imgui.h"

#include "../Include/Test.h"

class TestTexture2D : public Test {
public:
    TestTexture2D();
    ~TestTexture2D();
    
    void OnUpdate(float delta) override;
    void OnRender() override;
    void OnGuiRender() override;
private:
    ImVec4 _color;

    Renderer _renderer;

    std::unique_ptr<VertexArray> _vao;
    std::unique_ptr<IndexBuffer> _indexBuffer;
    std::unique_ptr<Shader> _shader;
    std::unique_ptr<Texture2D> _texture;
    std::unique_ptr<VertexBuffer> _vertexBuffer;

    glm::mat4 _projection;
    glm::mat4 _viewMatrix;

    glm::vec3 _translationA;
    glm::vec3 _translationB;

    ImVec4 _colorA = {1,1,1,1};
    ImVec4 _colorB = {1,1,1,1};
};

#endif /* TEST_TEXTURE_2D_H */