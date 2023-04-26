#include "TestMenu.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "TestClearColor.h"
#include "TestTexture.h"

#include "Utils.h"

namespace test
{
    TestMenu::TestMenu()
    {
    }

    TestMenu::~TestMenu()
    {
        for (auto& registeredTest : m_registeredTests)
        {
            SAFE_DELETE(registeredTest.m_instance);
        }
    }

    void TestMenu::OnUpdate(float deltaTime)
    {
        for (auto& registeredTest : m_registeredTests)
        {
            if (registeredTest.m_active && !registeredTest.m_instance)
            {
                registeredTest.m_instance = registeredTest.m_constructor();
                registeredTest.m_instance->SetRenderer(m_Renderer);
                registeredTest.m_instance->SetName(registeredTest.m_name);
            }
            else if (!registeredTest.m_active && registeredTest.m_instance)
            {
                SAFE_DELETE(registeredTest.m_instance);
            }

            if (registeredTest.m_instance)
            {
                registeredTest.m_instance->OnUpdate(deltaTime);
            }
        }
    }

    void TestMenu::OnRender()
    {
        for (auto& registeredTest : m_registeredTests)
        {
            if(registeredTest.m_instance)
            registeredTest.m_instance->OnRender();
        }
    }

    void TestMenu::OnImGuiRender()
    {
        if (ImGui::CollapsingHeader("Test list:", true))
        {
            for (auto& registeredTest : m_registeredTests)
            {
                char buffer[256];
                std::sprintf(buffer, "Load %s", registeredTest.m_name);
                ImGui::Checkbox(buffer, &registeredTest.m_active);
            }
        }

        for (auto& registeredTest : m_registeredTests)
        {
            if (registeredTest.m_instance)
            registeredTest.m_instance->OnImGuiRender();
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }

    void TestMenu::ReserveRegisteredTests(unsigned int size)
    {
        m_registeredTests.reserve(size);
    }
}
