#ifndef LOG_H
#define LOG_H

#include <csignal>
#include <iostream>
#include <GL/glew.h>

/* -------------------- Error logging -------------------- */

/**
 * Print info log
 */
#define INFO(x) std::cout << "[INFO]: " << x << std::endl
/**
 * Print warning log
 */
#define WARN(x) std::cout << "[WARNING]: " << x << std::endl
/**
 * Print regular error log
 */
#define ERROR(x) std::cout << "[ERROR]: " << x << std::endl
/**
 * Print GL error log
 */
#define GL_ERROR(x, y, z, w) std::cout << "[GL ERROR]: (" << x << ")" << " \nFunction: " << y << " \nFile: " << z << " \nLine: " << w << std::endl

/**
 * Assert statement and raise exception if false
 */
#define ASSERT(x) if (!(x)) std::raise(SIGINT);
/**
 * Assert GL function and Create GL Logcall
 */
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) 


/**
 * Clears the GL error log
 */
void GLClearError();

/**
 * Creates a GL Logcall
 */
bool GLLogCall(const char* function, const char* file, int line);



#endif /* LOG_H */