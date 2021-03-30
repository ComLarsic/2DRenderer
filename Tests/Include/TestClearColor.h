#ifndef TEST_CLEAR_COLOR_H
#define TEST_CLEAR_COLOR_H

#include <GL/glew.h>

#include "../../Include/Log.h"
#include "../../Include/Renderer.h"

#include "../../Vendor/imgui/imgui.h"

#include "../Include/Test.h"

class TestClearColor : public Test {
public:
    TestClearColor();
    ~TestClearColor();

    void OnRender() override;
    void OnGuiRender() override;
private:
    ImVec4 _color;
};

#endif /* TEST_CLEAR_COLOR_H */