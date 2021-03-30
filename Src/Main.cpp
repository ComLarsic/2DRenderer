#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <csignal>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Vendor/imgui/imgui.h"
#include "../Vendor/imgui/imgui_impl_glfw.h"
#include "../Vendor/imgui/imgui_impl_opengl3.h"


#include "../Include/Renderer.h"
#include "../Include/VertexBuffer.h"
#include "../Include/IndexBuffer.h"
#include "../Include/VertexArray.h"
#include "../Include/Shader.h"
#include "../Include/Texture.h"

#include "../Tests/Include/Test.h"
#include "../Tests/Include/TestClearColor.h"
#include "../Tests/Include/TestTexture2D.h"
#include "../Tests/Include/TestBatchRendering.h"

/* -------------------- Rendering code -------------------- */

int main(int argc, char **argv) {
    GLFWwindow* window;

    // Initialize SDL
    if (!glfwInit()) {
        ERROR("Failed to initialize SDL");
        return -1;
    }

    /* --- Create window --- */
    window = glfwCreateWindow(1280, 720, "Rendering tests!", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    
    glfwSetWindowAttrib(window, GL_MAJOR_VERSION, 3);
    glfwSetWindowAttrib(window, GL_MINOR_VERSION, 2);
    glfwSetWindowAttrib(window, GL_CONTEXT_PROFILE_MASK, GL_CONTEXT_CORE_PROFILE_BIT);

    // Initializ glew
    if (glewInit() != GLEW_OK) { 
        ERROR("Failed to initialize glew");
        return -1;
    }


    /* --- Initialize game --- */

    INFO("GL version: " << glGetString(GL_VERSION));

    // Setup blending
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    // Init ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    // Create test menu
    Test* currentTest = nullptr;
    auto* menu = new TestMenu(currentTest);

    menu->RegisterTest<TestClearColor>("Clear color");
    menu->RegisterTest<TestTexture2D>("Texture test");
    menu->RegisterTest<TestBatchRendering>("Batch rendering test");

    auto* t = new TestBatchRendering();

    for (int count = 0; !glfwWindowShouldClose(window); count++) {
        glfwPollEvents();

        currentTest->OnUpdate(ImGui::GetIO().DeltaTime);
        currentTest->OnRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Performance");
        ImGui::Text("FPS: %.0f \nDeltaTime: %.10f", ImGui::GetIO().Framerate, ImGui::GetIO().DeltaTime);
        ImGui::End();

        if (currentTest) {
            currentTest->OnUpdate(ImGui::GetIO().DeltaTime);
            currentTest->OnRender();

            ImGui::Begin("Test");
            if (currentTest != menu && ImGui::Button("<-")) { 
                delete currentTest;
                currentTest = menu;
            }
            currentTest->OnGuiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        GLCall(glViewport(0, 0, 1280, 720));

        INFO("Current frame: " << count);
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    delete menu;

    glfwTerminate();
    return 0;
}