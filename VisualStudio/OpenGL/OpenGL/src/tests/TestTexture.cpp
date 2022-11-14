#include "TestTexture.h"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
    TestTexture::TestTexture(Renderer& renderer)
        :m_Positions(nullptr),
        m_Indecies(nullptr),
        m_va(nullptr),
        m_vb(nullptr),
        m_layout(nullptr),
        m_ib(nullptr),
        m_shader(nullptr),
        m_texture(nullptr),
        myRenderer(&renderer),
        m_translation(0.0f, 0.0f, 0.0f),
        m_proj(glm::ortho(-1.0f * g_Aspect, 1.0f * g_Aspect, -1.0f, 1.0f, -1.0f, 1.0f)),
        m_color(1.0f, 1.0f, 1.0f, 1.0f),
        m_colorIncrement(0.05f, 0.08f, 0.03f, 0.0f),
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
        if (m_Positions)
        {
            delete[] m_Positions;
            m_Positions = nullptr;
        }

        if (m_Indecies)
        {
            delete[] m_Indecies;
            m_Indecies = nullptr;
        }

        if (m_va)
        {
            delete m_va;
            m_va = nullptr;
        }

        if (m_vb)
        {
            delete m_va;
            m_va = nullptr;
        }

        if (m_layout)
        {
            delete m_va;
            m_va = nullptr;
        }

        if (m_ib)
        {
            delete m_ib;
            m_ib = nullptr;
        }

        if (m_shader)
        {
            delete m_shader;
            m_shader = nullptr;
        }

        if (m_texture)
        {
            delete m_texture;
            m_texture = nullptr;
        }
    }

    void TestTexture::OnUpdate(float deltaTime)
    {
        m_color += m_colorIncrement;
        float r = m_color.r;
        float g = m_color.g;
        float b = m_color.b;
        m_colorIncrement.r = 0.05f * (r < 0.0f) - 0.05f * (r > 1.0f) + m_colorIncrement.r * (r <= 1.0f && r >= 0.0f);
        m_colorIncrement.g = 0.08f * (g < 0.0f) - 0.08f * (g > 1.0f) + m_colorIncrement.g * (g <= 1.0f && g >= 0.0f);;
        m_colorIncrement.b = 0.03f * (b < 0.0f) - 0.03f * (b > 1.0f) + m_colorIncrement.b * (b <= 1.0f && b >= 0.0f);;
    }

    void TestTexture::OnRender()
    {
        m_texture->Bind();
        m_shader->Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
        glm::mat4 mvp = m_proj * m_view * model;
        m_shader->SetUniform4f("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
        m_shader->SetUniformMat4f("u_MVP", mvp);
        myRenderer->Draw(*m_va, *m_ib, *m_shader);
    }

    void TestTexture::OnImGuiRender()
    {

    }
}