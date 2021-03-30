#include "../Include/VertexArray.h"
#include "../Include/Renderer.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &_rendererID));
    GLCall(glBindVertexArray(_rendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    for (int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.Count, element.Type, element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*) offset));
        offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
    }
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(_rendererID));
}

void VertexArray::UnBind() const {
    GLCall(glBindVertexArray(0));
}