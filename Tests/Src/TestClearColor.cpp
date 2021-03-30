#include "../Include/Test.h"
#include "../Include/TestClearColor.h"

TestClearColor::TestClearColor() {
    _color = {1,1,1,1};
}

TestClearColor::~TestClearColor() {

}

void TestClearColor::OnRender() {
    GLCall(glClearColor(_color.x, _color.y, _color.z, _color.w));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnGuiRender() {
    ImGui::Begin("Color control");
    ImGui::ColorPicker4("Clear color", &_color.x);
    ImGui::End();
}
