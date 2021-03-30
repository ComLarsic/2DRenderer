#ifndef TEST_BATCH_RENDERER_H
#define TEST_BATCH_RENDERER_H

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

class TestBatchRendering : public Test {
public:
    TestBatchRendering();
    ~TestBatchRendering();

    void OnRender() override;
    void OnGuiRender() override;
private:
    Renderer _renderer;

    VertexArray* _vao;
    IndexBuffer* _indexBuffer;
    Shader* _shader;
    Texture2D* _texture;
    VertexBuffer* _vertexBuffer;

    glm::mat4 _projection;
    glm::mat4 _viewMatrix;

    int _renderAmount;
    int _zoom = 1;
    glm::vec3 _camPosition = glm::vec3(0, 0, 0);
};

#endif /* TEST_BATCH_RENDERER_H */