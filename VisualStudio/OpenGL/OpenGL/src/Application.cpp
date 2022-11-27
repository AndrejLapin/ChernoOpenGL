#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture.h"
#include "tests/TestTrueTexture.h"
#include "tests/TestBatchRendering.h"
#include "tests/TestMenu.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(g_Width, g_Height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(0); // Enable vsync. Sometimes vsync can be enabled by default, to disable pass 0 as parameter.

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        Renderer renderer;

        // Setup Dear ImGui context
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        test::TestMenu menu;
        menu.SetRenderer(&renderer);
        menu.ReserveRegisteredTests(4);
        menu.RegisterTest<test::TestClearColor>("Clear color");
        menu.RegisterTest<test::TestTexture>("Texture");
        menu.RegisterTest<test::TestTrueTexture>("TrueTexture");
        menu.RegisterTest<test::TestBatchRendering>("Batch Rendering");

        double frameDeltaTime = 0.0f;

        while (!glfwWindowShouldClose(window))
        {
            auto start = std::chrono::steady_clock::now();
            /* Render here */
            renderer.Clear();

            menu.OnUpdate(frameDeltaTime);
            menu.OnRender();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            menu.OnImGuiRender();

            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            //glDrawArrays(GL_TRIANGLES, 0, 6);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            auto end = std::chrono::steady_clock::now();
            frameDeltaTime = std::clamp((std::chrono::duration<double>(end - start)).count(), 0.0, 0.1);
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}