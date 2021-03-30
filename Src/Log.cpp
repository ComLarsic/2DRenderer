/* -------------------- Error logging -------------------- */

#include "../Include/Log.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        GL_ERROR(error, function, file, line);
        return false;
    }

    return true;
}
