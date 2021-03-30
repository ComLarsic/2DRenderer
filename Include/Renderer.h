#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <csignal>
#include <GL/glew.h>
#include <GL/gl.h>

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Color.h"

/* -------------------- Rendering code -------------------- */

class Renderer {
private:
    Color _clearColor;

public:
    void SetClearColor(Color color);
    Color GetClearColor() { return _clearColor; }

    void Clear();
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif /* RENDERER_H */
