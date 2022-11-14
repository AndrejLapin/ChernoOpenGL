#pragma once

#include "Test.h"

namespace test
{
    class TestMenu : public Test
    {
    public:
        TestMenu();
        ~TestMenu();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
    };
}
