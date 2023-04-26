#include "TestTexture.h"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Utils.h"

#include "imgui/imgui.h"

namespace test
{
    TestTexture::TestTexture()
        :m_Positions(nullptr),
        m_Indecies(nullptr),
        m_va(nullptr),
        m_vb(nullptr),
        m_layout(nullptr),
        m_ib(nullptr),
        m_shader(nullptr),
        m_texture(nullptr),
        m_translation(0.0f, 0.0f, 0.0f),
        m_proj(glm::ortho(-1.0f * g_Aspect, 1.0f * g_Aspect, -1.0f, 1.0f, -1.0f, 1.0f)),
        m_color(1.0f, 1.0f, 1.0f, 1.0f),
        m_colorIncrement(3.0f, 4.8f, 1.8f, 0.0f),
        m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    {
        m_Positions = new float[16] {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
        };

        m_Indecies = new unsigned int[6] {
            0, 1, 2,
            2, 3, 0,
        };

        m_va        =   new VertexArray();
        m_vb        =   new VertexBuffer(m_Positions, 4 * 4 * sizeof(float));
        m_layout    =   new VertexBufferLayout();
        

        m_ib        =   new IndexBuffer(m_Indecies, 6);

        m_shader    =   new Shader("res/shaders/Texture_x_Color.shader");
        m_texture   =   new Texture("res/textures/SquirtleCloseUp.png");

        m_layout->Push<float>(2);
        m_layout->Push<float>(2);
        m_va->AddBuffer(*m_vb, *m_layout);

        m_shader->Bind();
        m_texture->Bind();
        m_shader->SetUniform1i("u_Texture", 0);

        m_vb->Unbind();
        m_ib->Unbind();
        m_shader->Unbind();
        m_texture->Unbind();
    }

    TestTexture::~TestTexture()
    {
        SAFE_DELETE_ARRAY(m_Positions);
        SAFE_DELETE_ARRAY(m_Indecies);
        SAFE_DELETE(m_va);
        SAFE_DELETE(m_vb);
        SAFE_DELETE(m_layout);
        SAFE_DELETE(m_ib);
        SAFE_DELETE(m_shader);
        SAFE_DELETE(m_texture);
    }

    void TestTexture::OnUpdate(float deltaTime)
    {
        m_color += m_colorIncrement *deltaTime;
        float r = m_color.r;
        float g = m_color.g;
        float b = m_color.b;
        m_colorIncrement.r = 3.0f * (r < 0.0f) - 3.0f * (r > 1.0f) + m_colorIncrement.r * (r <= 1.0f && r >= 0.0f);
        m_colorIncrement.g = 4.8f * (g < 0.0f) - 4.8f * (g > 1.0f) + m_colorIncrement.g * (g <= 1.0f && g >= 0.0f);
        m_colorIncrement.b = 1.8f * (b < 0.0f) - 1.8f * (b > 1.0f) + m_colorIncrement.b * (b <= 1.0f && b >= 0.0f);
    }

    void TestTexture::OnRender()
    {
        m_texture->Bind();
        m_shader->Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->SetUniform4f("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
        m_shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_va, *m_ib, *m_shader);
    }

    void TestTexture::OnImGuiRender()
    {
        if (ImGui::CollapsingHeader(m_Name, false))
        {
            ImGui::SliderFloat3("Translation", &m_translation.x, -1.5f, 1.5f);
        }
    }
}