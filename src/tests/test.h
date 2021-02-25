#ifndef __TEST_H__
#define __TEST_H__

#include "log.h"
#include <vector>
#include <string>
#include <functional>

namespace test
{
    class baseTest;
    class testPool
    {
        typedef std::pair<std::string, std::function<baseTest*()> > testType;
    public:
        static void Register();
        static void update();
        static void reset();
    private:
        testPool() {}
        ~testPool() {}
        template <typename T>
        void addTest(const char* tag, const char* name) {
            get()._list.emplace_back( tag, [](){ return new T; } );
            OPENGL_INFO( "Test \'{}\' registered.", name );
        }
        void onImGui();
        void onRenderer();
        static inline testPool& get() {
            static testPool t;
            return t;
        }
    private:
        std::vector<testType>   _list;
        baseTest*               _curTest = NULL;
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

#define TEST_CLASS_PUBLIC(className)        \
    public:                                 \
        className() {}                      \
        ~className() {}                     \
        void onUpdate(float time) override; \
        void onRenderer() override;         \
        void onImGui() override;

    class testClearColor : public baseTest
    {
        TEST_CLASS_PUBLIC( testClearColor )
    private:
        float   _color[4] = { 0.2f, 0.3f, 0.3f, 1.0f };
    };
}

#endif /* __TEST_H__ */
