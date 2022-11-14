#include "TestMenu.h"

//#include "Renderer.h"
#include "imgui/imgui.h"

test::TestMenu::TestMenu()
{
}

test::TestMenu::~TestMenu()
{
}

void test::TestMenu::OnUpdate(float deltaTime)
{
}

void test::TestMenu::OnRender()
{
}

void test::TestMenu::OnImGuiRender()
{
    // try different buttons here
    ImGui::Button("Load test X");
}
