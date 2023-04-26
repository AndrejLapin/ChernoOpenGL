#pragma once

#include "Test.h"
#include <unordered_map>
#include <functional>

//#include "TestTexture.h"
//#include "TestClearColor.h"


class Renderer;

/*
* Design options:
* Option 1: have a vector of registered tests
*   struct RegisteredTest {
*       std::string testName;
*       bool shouldBeActive;
*       pointer to test constructor;
*       Test* myTest;
*   }
*   OnUpdate iterate through vector of registered tests, check if tests shouldBeActive and create/unasign myTest
*   OnRender and OnImGuiRender iterate through the entire registered tests vector
* Option 2: also have a vector of active tests and have an index in which this test is stored on a vector.
*/

namespace test
{
    struct RegisteredTest {
        const char* m_name;
        bool m_active;
        std::function<Test*()> m_constructor;
        Test* m_instance;
        //unsigned int m_activeVectorIndex;

        RegisteredTest(const char* name, std::function<Test* ()> constructor) : m_name(name), m_constructor(constructor), m_active(false), m_instance(nullptr)/*, m_activeVectorIndex(-1)*/{}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu();
        ~TestMenu();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const char* testName)
        {
            m_registeredTests.emplace_back(testName, []() { return new T(); });
        }

        void ReserveRegisteredTests(unsigned int size);

    private:
        std::vector<RegisteredTest> m_registeredTests;
    };
}
