#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
        };

        unsigned int indecies[] = {
            0, 1, 2,
            2, 3, 0,
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indecies, 6);

        Shader shader("res/shaders/Texture_x_Color.shader");
        //Shader shader("res/shaders/Texture+Color.shader");
        //Shader shader("res/shaders/Texture.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        //Texture texture("res/textures/FreshNewAvatar.png");
        Texture texture("res/textures/SquirtleCloseUp.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float rIncrement = 0.05f;
        float g = 0.5f;
        float gIncrement = 0.08f;
        float b = 1.0f;
        float bIncrement = 0.03f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, g, b, 1.0f);

            renderer.Draw(va, ib, shader);

            rIncrement = 0.05f * (r < 0.0f) - 0.05f * (r > 1.0f) + rIncrement * (r <= 1.0f && r >= 0.0f);
            gIncrement = 0.08f * (g < 0.0f) - 0.08f * (g > 1.0f) + gIncrement * (g <= 1.0f && g >= 0.0f);;
            bIncrement = 0.03f * (b < 0.0f) - 0.03f * (b > 1.0f) + bIncrement * (b <= 1.0f && b >= 0.0f);;

            r += rIncrement;
            g += gIncrement;
            b += bIncrement;

            //glDrawArrays(GL_TRIANGLES, 0, 6);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}