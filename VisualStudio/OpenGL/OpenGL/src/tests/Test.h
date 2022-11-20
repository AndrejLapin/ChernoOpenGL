#pragma once

class Renderer;

namespace test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}

        void SetName(const char* name) { m_Name = name; }
        void SetRenderer(Renderer* renderer) { m_Renderer = renderer; }

    protected:
        Renderer* m_Renderer;
        const char* m_Name;
    };
}