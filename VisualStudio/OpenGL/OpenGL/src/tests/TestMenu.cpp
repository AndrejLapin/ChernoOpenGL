#include "TestMenu.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "TestClearColor.h"
#include "TestTexture.h"

namespace test
{
    const std::string TestMenu::TestNames::m_ClearColor = "ClearColor";
    const std::string TestMenu::TestNames::m_Texture = "Texture";

    TestMenu::TestMenu(Renderer& renderer)
        :m_enableClearColor(false),
        m_enableTextureTest(false),
        myRenderer(&renderer)
    {
    }

    TestMenu::~TestMenu()
    {
        for (auto test : m_testList)
        {
            if (test.second)
            {
                delete(test.second);
                test.second = nullptr;
            }
        }
        m_testList.clear();
    }

    void TestMenu::OnUpdate(float deltaTime)
    {
        for (auto test : m_testList)
        {
            test.second->OnUpdate(deltaTime);
        }

        if (m_enableClearColor && m_testList.find(TestNames::m_ClearColor) == m_testList.end())
        {
            m_testList[TestNames::m_ClearColor] = new TestClearColor();
        }
        else if (!m_enableClearColor && m_testList.find(TestNames::m_ClearColor) != m_testList.end())
        {
            delete(m_testList[TestNames::m_ClearColor]);
            m_testList.erase(TestNames::m_ClearColor);
        }

        if (m_enableTextureTest && m_testList.find(TestNames::m_Texture) == m_testList.end())
        {
            m_testList[TestNames::m_Texture] = new TestTexture(*myRenderer);
        }
        else if (!m_enableTextureTest && m_testList.find(TestNames::m_Texture) != m_testList.end())
        {
            delete(m_testList[TestNames::m_Texture]);
            m_testList.erase(TestNames::m_Texture);
        }
    }

    void TestMenu::OnRender()
    {
        for (auto test : m_testList)
        {
            test.second->OnRender();
        }
    }

    void TestMenu::OnImGuiRender()
    {
        ImGui::Checkbox("Load clear color test", &m_enableClearColor);
        ImGui::Checkbox("Load texture test", &m_enableTextureTest);

        for (auto test : m_testList)
        {
            test.second->OnImGuiRender();
        }
    }
}
