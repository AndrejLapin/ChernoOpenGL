#pragma once

#include "Test.h"

class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Shader;
class TrueTexture;
class Renderer;

#include "glm/glm.hpp"

namespace test
{
    class TestTrueTexture :public Test
    {
    public:
        TestTrueTexture();
        ~TestTrueTexture();

        void OnUpdate(float deltaTime);
        void OnRender();
        void OnImGuiRender();
    private:
        float* m_Positions;
        unsigned int* m_Indecies;

        glm::vec3 m_translation;
        glm::vec3 m_scale;
        float m_scaleMultiplier;

        glm::mat4 m_proj;
        glm::mat4 m_view;

        glm::vec4 m_color;
        glm::vec4 m_colorIncrement;

        VertexArray* m_va;
        VertexBuffer* m_vb;
        VertexBufferLayout* m_layout;
        IndexBuffer* m_ib;
        Shader* m_shader;
        TrueTexture* m_texture;
    };
}
