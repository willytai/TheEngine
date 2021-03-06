#include "core/util/log.h"

namespace Engine7414
{
    std::shared_ptr<spdlog::logger> Log::__glfwLogger;
    std::shared_ptr<spdlog::logger> Log::__openglLogger;
    std::shared_ptr<spdlog::logger> Log::__systemLogger;
    std::shared_ptr<spdlog::logger> Log::__engineLogger;
    std::shared_ptr<spdlog::logger> Log::__backendLogger;

    void Log::init(int verbosity) {
        switch (verbosity) {
            case 0:
                Log::init( spdlog::level::off );
                break;
            case 1:
                Log::init( spdlog::level::warn );
                break;
            case 2:
                Log::init( spdlog::level::info );
                break;
            case 4:
                Log::init( spdlog::level::trace );
                break;
            default:
                Log::init( spdlog::level::trace );
                break;
        }
    }

    void Log::init(spdlog::level::level_enum log_level) {
        spdlog::set_pattern( "%^[%n::%l] %v%$" );

        __glfwLogger = spdlog::stdout_color_mt( "glfw" );
        __glfwLogger->set_level( log_level );
        __glfwLogger->trace( "logger initialized" );
        __glfwLogger->flush_on( spdlog::level::debug );

        __openglLogger = spdlog::stdout_color_mt( "OpenGL" );
        __openglLogger->set_level( log_level );
        __openglLogger->trace( "logger initialized" );
        __openglLogger->flush_on( spdlog::level::debug );

        __systemLogger = spdlog::stdout_color_mt( "System" );
        __systemLogger->set_level( log_level );
        __systemLogger->trace( "logger initialized" );
        __systemLogger->flush_on( spdlog::level::debug );

        __engineLogger = spdlog::stdout_color_mt( "Core" );
        __engineLogger->set_level( log_level );
        __engineLogger->trace( "logger initialized" );
        __engineLogger->flush_on( spdlog::level::debug );

        __backendLogger = spdlog::stdout_color_mt( "Backend" );
        __backendLogger->set_level( log_level );
        __backendLogger->trace( "logger initialized" );
        __backendLogger->flush_on( spdlog::level::debug );
    }
}
