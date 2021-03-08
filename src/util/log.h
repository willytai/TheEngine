#ifndef __LOG_H__
#define __LOG_H__

#ifdef NDEBUG
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#else
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace util
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

#define GLFW_TRACE(...) ::util::Log::getGLFWlogger()->trace(__VA_ARGS__)
#define GLFW_DEBUG(...) ::util::Log::getGLFWlogger()->debug(__VA_ARGS__)
#define GLFW_WARN(...)  ::util::Log::getGLFWlogger()->warn(__VA_ARGS__)
#define GLFW_INFO(...)  ::util::Log::getGLFWlogger()->info(__VA_ARGS__)
#define GLFW_ERROR(...) ::util::Log::getGLFWlogger()->error(__VA_ARGS__)

#define OPENGL_TRACE(...) ::util::Log::getOpenGLlogger()->trace(__VA_ARGS__)
#define OPENGL_DEBUG(...) ::util::Log::getOpenGLlogger()->debug(__VA_ARGS__)
#define OPENGL_WARN(...)  ::util::Log::getOpenGLlogger()->warn(__VA_ARGS__)
#define OPENGL_INFO(...)  ::util::Log::getOpenGLlogger()->info(__VA_ARGS__)
#define OPENGL_ERROR(...) ::util::Log::getOpenGLlogger()->error(__VA_ARGS__)

#define SYS_TRACE(...) ::util::Log::getSystemlogger()->trace(__VA_ARGS__)
#define SYS_DEBUG(...) ::util::Log::getSystemlogger()->debug(__VA_ARGS__)
#define SYS_WARN(...)  ::util::Log::getSystemlogger()->warn(__VA_ARGS__)
#define SYS_INFO(...)  ::util::Log::getSystemlogger()->info(__VA_ARGS__)
#define SYS_ERROR(...) ::util::Log::getSystemlogger()->error(__VA_ARGS__)

#define CORE_TRACE(...) ::util::Log::getEnginelogger()->trace(__VA_ARGS__)
#define CORE_DEBUG(...) ::util::Log::getEnginelogger()->debug(__VA_ARGS__)
#define CORE_WARN(...)  ::util::Log::getEnginelogger()->warn(__VA_ARGS__)
#define CORE_INFO(...)  ::util::Log::getEnginelogger()->info(__VA_ARGS__)
#define CORE_ERROR(...) ::util::Log::getEnginelogger()->error(__VA_ARGS__)

#define BACKEND_TRACE(...) ::util::Log::getBackendlogger()->trace(__VA_ARGS__)
#define BACKEND_DEBUG(...) ::util::Log::getBackendlogger()->debug(__VA_ARGS__)
#define BACKEND_WARN(...)  ::util::Log::getBackendlogger()->warn(__VA_ARGS__)
#define BACKEND_INFO(...)  ::util::Log::getBackendlogger()->info(__VA_ARGS__)
#define BACKEND_ERROR(...) ::util::Log::getBackendlogger()->error(__VA_ARGS__)

#endif /* __LOG_H__ */
