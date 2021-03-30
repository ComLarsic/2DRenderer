#include "../Include/VertexBufferLayout.h"

template<typename T>
void VertexBufferLayout::Push(unsigned int count) {
    ASSERT(false);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
    _elements.push_back({GL_FLOAT, count, false});
    _stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    _elements.push_back({GL_UNSIGNED_INT, count, false});
    _stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
    _elements.push_back({GL_UNSIGNED_BYTE, count, true});
    _stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
