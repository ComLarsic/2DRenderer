#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <vector>
#include <functional>

#include <GL/glew.h>

#include "../../Include/Log.h"

#include "../../Vendor/imgui/imgui.h"

class Test {
public:
    Test() {}
    ~Test() {}

    virtual void Init() {};
    virtual void OnUpdate(float delta) {};
    virtual void OnRender() {};
    virtual void OnGuiRender() {};
};

class TestMenu : public Test {
public:
    TestMenu(Test*& currentTestPointer);
    ~TestMenu();

    void OnGuiRender() override;
    void OnRender() override;

    template <typename T>
    void RegisterTest(const std::string& name) {
        _tests.push_back(std::make_pair(name, []() { return new T(); } ));
    };

private:
    Test*& _currentTest;
    std::vector<std::pair<std::string, std::function<Test*()>>> _tests;
};

#endif /* TEST_H */
