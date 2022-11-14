#pragma once

#include "Test.h"
#include <unordered_map>

class Renderer;

namespace test
{
    class TestMenu : public Test
    {
    public:
        TestMenu(Renderer& renderer);
        ~TestMenu();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unordered_map<std::string, Test*> m_testList;
        bool m_enableClearColor;
        bool m_enableTextureTest;

        Renderer* myRenderer;

        struct TestNames
        {
            static const std::string m_ClearColor;
            static const std::string m_Texture;
        };
    };
}
