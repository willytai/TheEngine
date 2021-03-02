#ifndef __TEST_H__
#define __TEST_H__

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif

#include "renderer.h"
#include "log.h"
#include "imgui.h"
#include <vector>
#include <string>
#include <functional>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#define TEST_CLASS_PUBLIC(className)        \
    public:                                 \
        className(const char* name);        \
        ~className();                       \
        void onUpdate(float time) override; \
        void onRenderer() override;         \
        void onImGui() override;

namespace test
{
    class baseTest;

    class testPool
    {
        typedef std::pair<std::string, std::function<baseTest*()> > testType;
    public:
        static void init(GLFWwindow* window);
        static void test(float deltaTime);
        static void reset();
        static void updateWindowTitle(const char* name);
        inline static GLFWwindow* getGLFWwindow() { return get()._window; }
    private:
        testPool() {}
        ~testPool() {}
        template <typename T>
        void addTest(const char* tag, const char* name) {
            get()._list.emplace_back( tag, [=](){ return new T(tag); } );
            OPENGL_INFO( "Test \'{}\' registered.", name );
        }
        void onUpdate(const float& deltaTime);
        void onImGui();
        void onRenderer();
        static inline testPool& get() {
            static testPool t;
            return t;
        }
    private:
        std::vector<testType>   _list;
        baseTest*               _curTest = NULL;
        GLFWwindow*             _window  = NULL;
    };

    class baseTest
    {
    public:
        baseTest() {}
        virtual ~baseTest() {}

        virtual void onUpdate(float time) {}
        virtual void onRenderer() {}
        virtual void onImGui() {}
    };



    /**************************************************
    *                    Test Units                   *
    **************************************************/

    class testClearColor : public baseTest
    {
        TEST_CLASS_PUBLIC( testClearColor )
    private:
        float   _color[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
    };

    // -------------------------------------------------

    class testColoredCube : public baseTest
    {
        TEST_CLASS_PUBLIC( testColoredCube )
    private:
        Shader          __shader;
        glm::mat4       __perspective;
        glm::vec3       __m_translation;
        glm::vec3       __m_rotation;
        float           __m_scale;
        float           __camera_height;
        VertexArray     __va;
        IndexBufferUI*  __ib;
    };

    // -------------------------------------------------

    class testCamera : public baseTest
    {
        TEST_CLASS_PUBLIC( testCamera )
    private:
        Shader          __shader;
        Camera*         __camera;
        VertexArray     __va;
        IndexBufferUI*  __ib;
    };

    // -------------------------------------------------

    class testLighting : public baseTest
    {
        TEST_CLASS_PUBLIC( testLighting )
    private:
        Shader          __shader;
        float           __ambient;
        glm::vec3       __lightPosOffset;
        glm::vec3       __lightColor;
        glm::vec3       __objPosOffset;
        glm::vec3       __objColor;
        Camera*         __camera;
        VertexArray     __vaCube;
        VertexArray     __vaLight;
        IndexBufferUI*  __ib;
    };

    // -------------------------------------------------
}

#endif /* __TEST_H__ */
