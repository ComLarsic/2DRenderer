#include <GL/glew.h>
#include <GL/gl.h>

#include "../Include/Test.h"
#include "../Include/TestTexture2D.h"

TestTexture2D::TestTexture2D() : 
_translationA(glm::vec3(200, 200, 0)), _translationB(glm::vec3(400, 200, 0)), 
_projection(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)), _viewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0))) {
    _color = {1,1,1,1};

    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,
         50.0f, -50.0f, 1.0f, 0.0f,
         50.0f,  50.0f, 1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    GLCall(glEnable(GL_BLEND))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    _vertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    
    layout.Push<float>(2);
    layout.Push<float>(2);
    
    _vao = std::make_unique<VertexArray>();
    _vao->AddBuffer(*_vertexBuffer, layout);
    _indexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    _shader = std::make_unique<Shader>("Shaders/Default.shader");
    _shader->Bind();
    _shader->SetUniformColor("u_Color", WHITE);

    _texture = std::make_unique<Texture2D>("Res/TestingIcon.png");
    _texture->Bind();
}

TestTexture2D::~TestTexture2D() {

}

void TestTexture2D::OnUpdate(float delta) {

}

void TestTexture2D::OnRender() {
    GLCall(glClearColor(_color.x, _color.y, _color.z, _color.w));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    // Render textures
    _texture->Bind();

    // Texture A
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), _translationA);
        glm::mat4 mvp = _projection * _viewMatrix * model;
        _shader->Bind();
        _shader->SetUniformColor("u_Color", {_colorA.x * 255, _colorA.y * 255, _colorA.z * 255, _colorA.w * 255});
        _shader->SetUniformMat4f("u_MVP", mvp);
        _renderer.Draw(*_vao, *_indexBuffer, *_shader);
    }

    // Texture B
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0), _translationB);
        glm::mat4 mvp = _projection * _viewMatrix * model;
        _shader->Bind();
        _shader->SetUniformColor("u_Color", {_colorB.x * 255, _colorB.y * 255, _colorB.z * 255, _colorB.w * 255});
        _shader->SetUniformMat4f("u_MVP", mvp);
        _renderer.Draw(*_vao, *_indexBuffer, *_shader);
    }
}

void TestTexture2D::OnGuiRender() {
    ImGui::Begin("Texture Control");
    
    ImGui::SliderFloat3("Translation A", &_translationA.x, 0.0f, 1280.0f);
    ImGui::ColorPicker4("Color A", &_colorA.x);

    ImGui::SliderFloat3("Translation B", &_translationB.x, 0.0f, 1280.0f);
    ImGui::ColorPicker4("Color B", &_colorB.x);
    
    ImGui::End();
}
