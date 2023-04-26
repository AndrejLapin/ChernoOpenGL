#include "TestBatchRendering.h"

#include "glm/gtc/matrix_transform.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Utils.h"

#include "imgui/imgui.h"

test::TestBatchRendering::TestBatchRendering()
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
    m_colorIncrement(0.05f, 0.08f, 0.03f, 0.0f),
    m_view(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
    int vertexBufferSize = 72;

    m_Positions = new float[vertexBufferSize]{
         0.25f, -0.25f, 0.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,
         0.75f, -0.25f, 1.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,
         0.75f,  0.75f, 1.0f, 1.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,
         0.25f,  0.75f, 0.0f, 1.0f, 0.18f, 0.6f, 0.96f, 1.0f, 0.0f,

        -0.75f, -0.5f, 0.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f,
        -0.25f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
        -0.25f,  0.5f, 1.0f, 1.0f, 1.0f, 0.93f, 0.24f, 1.0f, 1.0f,
        -0.75f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
    };

    m_Indecies = new unsigned int[12]{
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,
    };

    //ColorVertexArray* newArr = new ColorVertexArray();

    m_va = new VertexArray();
    m_vb = new VertexBuffer(m_Positions, vertexBufferSize * sizeof(float));
    m_layout = new VertexBufferLayout();


    m_ib = new IndexBuffer(m_Indecies, 12);

    m_texture = new Texture("res/textures/SquirtleCloseUp.png");
    m_trueTexture = new Texture("res/textures/Character.png", Texture::NEAREST);

    m_shader = new Shader("res/shaders/BatchTexture.shader");
    m_shader->Bind();
    GLCall(auto loc = glGetUniformLocation(m_shader->GetRendererID(), "u_Textures"));
    int samplers[2] = { 0, 1 };
    GLCall(glUniform1iv(loc, 2 ,samplers));

    m_layout->Push<float>(2);
    m_layout->Push<float>(2);
    m_layout->Push<float>(4);
    m_layout->Push<float>(1);
    m_va->AddBuffer(*m_vb, *m_layout);

    m_shader->Bind();
    //m_texture->Bind();
    //m_shader->SetUniform1i("u_Texture", 0);

    m_vb->Unbind();
    m_ib->Unbind();
    m_shader->Unbind();
    m_texture->Unbind();
}

test::TestBatchRendering::~TestBatchRendering()
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

void test::TestBatchRendering::OnUpdate(float deltaTime)
{
}

void test::TestBatchRendering::OnRender()
{
    GLCall(glBindTextureUnit(0, m_texture->GetRendererId()));
    GLCall(glBindTextureUnit(1, m_trueTexture->GetRendererId()));
    m_shader->Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation);
    glm::mat4 mvp = m_proj;// *m_view* model;
    //m_shader->SetUniform4f("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);
    m_shader->SetUniformMat4f("u_MVP", mvp);
    //m_shader->SetUniform2f("u_aspect", g_Aspect, 1);
    m_Renderer->Draw(*m_va, *m_ib, *m_shader);
}

void test::TestBatchRendering::OnImGuiRender()
{
}
