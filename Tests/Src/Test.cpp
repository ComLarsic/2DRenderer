#include "../Include/Test.h"

TestMenu::TestMenu(Test*& currentTestPointer) : _currentTest(currentTestPointer) {
    _currentTest = this;
    GLCall(glClearColor(0,0,0,0));
}

TestMenu::~TestMenu() {

}

void TestMenu::OnRender() {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestMenu::OnGuiRender() {
    for (auto& test : _tests) {
        if(ImGui::Button(test.first.c_str()))
            _currentTest = test.second();
    }
}
