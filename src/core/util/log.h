#ifndef __LOG_H__
#define __LOG_H__

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable:4819)
#endif

#ifndef ENGINE_DEBUG
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#else
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef _MSC_VER
    #pragma warning(pop)
#endif

namespace Engine7414
{
    class Log
    {
    public:
        Log() {}
        ~Log() {};

        static void init(int verbosity = -1);
        static inline std::shared_ptr<spdlog::logger> getGLFWlogger() { return __glfwLogger; }
        static inline std::shared_ptr<spdlog::logger> getOpenGLlogger() { return __openglLogger; }
        static inline std::shared_ptr<spdlog::logger> getSystemlogger() { return __systemLogger; }
        static inline std::shared_ptr<spdlog::logger> getEnginelogger() { return __engineLogger; }
        static inline std::shared_ptr<spdlog::logger> getBackendlogger() { return __backendLogger; }

    private:
        static void init(spdlog::level::level_enum log_level);

    private:
        static std::shared_ptr<spdlog::logger>     __glfwLogger;
        static std::shared_ptr<spdlog::logger>     __openglLogger;
        static std::shared_ptr<spdlog::logger>     __systemLogger;
        static std::shared_ptr<spdlog::logger>     __engineLogger;
        static std::shared_ptr<spdlog::logger>     __backendLogger;
    };
}

#define GLFW_TRACE(...) ::Engine7414::Log::getGLFWlogger()->trace(__VA_ARGS__)
#define GLFW_DEBUG(...) ::Engine7414::Log::getGLFWlogger()->debug(__VA_ARGS__)
#define GLFW_WARN(...)  ::Engine7414::Log::getGLFWlogger()->warn(__VA_ARGS__)
#define GLFW_INFO(...)  ::Engine7414::Log::getGLFWlogger()->info(__VA_ARGS__)
#define GLFW_ERROR(...) ::Engine7414::Log::getGLFWlogger()->error(__VA_ARGS__)

#define OPENGL_TRACE(...) ::Engine7414::Log::getOpenGLlogger()->trace(__VA_ARGS__)
#define OPENGL_DEBUG(...) ::Engine7414::Log::getOpenGLlogger()->debug(__VA_ARGS__)
#define OPENGL_WARN(...)  ::Engine7414::Log::getOpenGLlogger()->warn(__VA_ARGS__)
#define OPENGL_INFO(...)  ::Engine7414::Log::getOpenGLlogger()->info(__VA_ARGS__)
#define OPENGL_ERROR(...) ::Engine7414::Log::getOpenGLlogger()->error(__VA_ARGS__)

#define SYS_TRACE(...) ::Engine7414::Log::getSystemlogger()->trace(__VA_ARGS__)
#define SYS_DEBUG(...) ::Engine7414::Log::getSystemlogger()->debug(__VA_ARGS__)
#define SYS_WARN(...)  ::Engine7414::Log::getSystemlogger()->warn(__VA_ARGS__)
#define SYS_INFO(...)  ::Engine7414::Log::getSystemlogger()->info(__VA_ARGS__)
#define SYS_ERROR(...) ::Engine7414::Log::getSystemlogger()->error(__VA_ARGS__)

#define CORE_TRACE(...) ::Engine7414::Log::getEnginelogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...) ::Engine7414::Log::getEnginelogger()->debug(__VA_ARGS__)
#define CORE_WARN(...)  ::Engine7414::Log::getEnginelogger()->warn(__VA_ARGS__)
#define CORE_INFO(...)  ::Engine7414::Log::getEnginelogger()->info(__VA_ARGS__)
#define CORE_ERROR(...) ::Engine7414::Log::getEnginelogger()->error(__VA_ARGS__)

#define BACKEND_TRACE(...) ::Engine7414::Log::getBackendlogger()->trace(__VA_ARGS__)
#define BACKEND_DEBUG(...) ::Engine7414::Log::getBackendlogger()->debug(__VA_ARGS__)
#define BACKEND_WARN(...)  ::Engine7414::Log::getBackendlogger()->warn(__VA_ARGS__)
#define BACKEND_INFO(...)  ::Engine7414::Log::getBackendlogger()->info(__VA_ARGS__)
#define BACKEND_ERROR(...) ::Engine7414::Log::getBackendlogger()->error(__VA_ARGS__)

#endif /* __LOG_H__ */
