#ifndef VERTEX_BUFFFER_H
#define VERTEX_BUFFFER_H

class VertexBuffer {
private:
    unsigned int _rendererID;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    /**
     * Bind the vertex buffer
     */
    void Bind() const;

    /**
     * Unbind the vertex buffer
     */
    void UnBind() const;
};

#endif /* VERTEX_BUFFFER_H */