#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include "Log.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>

struct VertexBufferElement {
    unsigned int Type;
    unsigned int Count;
    bool Normalized;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};


class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;

public:
    VertexBufferLayout() : _stride(0) {};

    /**
     * Add buffer element
     */
    template<typename T>
    void Push(unsigned int count);
    
    /**
     * Get buffer elements as vector
     */
    inline const std::vector<VertexBufferElement>& GetElements() const { return _elements; }
    
    /**
     * Get the current stride
     */
    inline unsigned int GetStride() const {return _stride; }
};

#endif /* VERTEX_BUFFER_LAYOUT_H */