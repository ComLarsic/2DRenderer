#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "Log.h"

class Texture2D {
private:
    unsigned int _rendererID;
    std::string _filePath;
    
    unsigned char* _localBuffer;
    int _width, _height, _bpp;
public:
    Texture2D(const std::string& filepath);
    ~Texture2D();

    void Bind(unsigned int slot = 0);
    void UnBind();

    inline int GetWidth() const { return _width; }
    inline int GetHeight() const { return _height; }
};

#endif