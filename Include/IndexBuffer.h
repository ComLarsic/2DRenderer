#ifndef INDEX_BUFFFER_H
#define INDEX_BUFFFER_H

class IndexBuffer {
public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    /**
     * Bind the vertex buffer
     */
    void Bind() const;

    /**
     * Unbind the vertex buffer
     */
    void UnBind() const;

    /**
     * Get the element count
     */
    inline unsigned int GetCount() const { return _count; }
private:
    unsigned int _rendererID;
    unsigned int _count;
};

#endif /* INDEX_BUFFFER_H */