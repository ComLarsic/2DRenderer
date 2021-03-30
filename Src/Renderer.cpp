#include "../Include/Renderer.h"

void Renderer::SetClearColor(Color color) {
    _clearColor = color;
    GLCall(glClearColor(color.R / 255, color.G / 255, color.B / 255, color.A / 255)); 
}

void Renderer::Clear() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
