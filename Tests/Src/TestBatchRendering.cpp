#include "../Include/TestBatchRendering.h"

TestBatchRendering::TestBatchRendering() : 
 _renderer(Renderer()) ,_projection(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)), _viewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0))), _renderAmount(0) {
    
    _renderAmount = 2;
    
    GLCall(glEnable(GL_BLEND))
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
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

    _vertexBuffer = new VertexBuffer(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    
    layout.Push<float>(2);
    layout.Push<float>(2);
    
    _vao = new VertexArray();
    _vao->AddBuffer(*_vertexBuffer, layout);
    _indexBuffer = new IndexBuffer(indices, 6);

    _shader = new Shader("Shaders/Default.shader");
    _shader->Bind();
    _shader->SetUniformColor("u_Color", WHITE);

    _texture = new Texture2D("Res/TestingIcon.png");
    _texture->Bind();
}

TestBatchRendering::~TestBatchRendering() {
    delete _vertexBuffer;
    delete _vao;
    delete _indexBuffer;
    delete _shader;
    delete _texture;
}

void TestBatchRendering::OnRender() {
    GLCall(glClearColor(0, 0, 0, 1));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    _projection = glm::ortho(0.0f, 1280.0f * _zoom, 0.0f, 720.0f * _zoom, -1.0f, 1.0f);
    _viewMatrix = glm::translate(glm::mat4(1.0f), _camPosition);

    _texture->Bind();

    for (int i = 0; i < _renderAmount; i++) {
        for(int j = 0; j < _renderAmount; j++) {
            glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(i * 100.0f, j * 100.0f, 0));
            glm::mat4 mvp = _projection * _viewMatrix * model;
    
            _shader->Bind();
            _shader->SetUniformMat4f("u_MVP", mvp);
            _renderer.Draw(*_vao, *_indexBuffer, *_shader);
        }
    }    
}

void TestBatchRendering::OnGuiRender() {
    ImGui::Begin("Texture controls");
    ImGui::InputInt("Amount", &_renderAmount);
    ImGui::End();

    ImGui::Begin("Camera Controls");
    ImGui::InputInt("Zoom out", &_zoom);
    ImGui::InputFloat3("Camera position", &_camPosition.x);
    ImGui::End();
}