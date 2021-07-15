cmake_minimum_required(VERSION 3.16)
project(TheEngine)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#enable_language(OBJCXX)

# compiler settings
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS       "-Wall -Wno-nullability-completeness -Wextra -pedantic-errors -Wconversion -Wno-gnu-anonymous-struct -Wno-nested-anon-types -Wformat")
set(CMAKE_C_FLAGS_DEBUG   "-g -DENGINE_DEBUG -DENGINE_BACKEND_OPENGL")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS     "-std=c++17 -Wall -Wno-nullability-completeness -Wextra -pedantic-errors -Wconversion -Wno-gnu-anonymous-struct -Wno-nested-anon-types -Wformat -ObjC++ -fobjc-weak -fobjc-arc")
set(CMAKE_CXX_FLAGS_DEBUG   "-g -DENGINE_DEBUG -DENGINE_BACKEND_OPENGL")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

#set(CMAKE_OBJCXX_FLAGS  "-std=c++17 -Wall -Wno-nullability-completeness -Wextra\\
#                         -pedantic-errors -Wconversion -Wno-gnu-anonymous-struct\\
#                         -Wno-nested-anon-types -Wformat -ObjC++")
#set(CMAKE_OBJCXX_FLAGS_DEBUG   "-g -DENGINE_DEBUG -DENGINE_BACKEND_OPENGL")
#set(CMAKE_OBJCXX_FLAGS_RELEASE "-O3 -DNDEBUG")


set(CMAKE_VERBOSE_MAKEFILE        OFF)
set(CMAKE_COLOR_MAKEFILE          ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD OFF)

set(CMAKE_BUILD_TYPE Debug)


# glfw
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

include_directories("src")
include_directories("vendor")
include_directories("vendor/spdlog/include")
include_directories("vendor/glad/include")
include_directories("vendor/stb/include")
include_directories("vendor/yaml-cpp/include")
include_directories("vendor/glm")
include_directories("vendor/imgui")

file(GLOB BACKEND "src/backend/MTL/*.cpp"
                  "src/backend/MTL/*.mm" )

file(GLOB_RECURSE CORE "src/core/*.cpp" "src/core/*.mm")
file(GLOB_RECURSE EDITOR "src/editor/*.cpp")
file(GLOB_RECURSE GLAD "src/glad*.c")

file(GLOB IMGUI "src/imgui/*.cpp"
                "src/imgui/*.mm" )

file(GLOB PLATFORM "src/platform/*.cpp"
                   "src/platform/Mac/*.cpp"
                   "src/platform/Mac/*.mm")

add_library(Engine SHARED ${BACKEND}
                          ${CORE}
                          ${EDITOR}
                          ${GLAD}
                          ${IMGUI}
                          ${PLATFORM})
#add_library(Engine STATIC ${BACKEND}
#                          ${CORE}
#                          ${EDITOR}
#                          ${GLAD}
#                          ${IMGUI}
#                          ${PLATFORM})

target_link_libraries(Engine "-framework Metal"
                             "-framework MetalKit"
                             "-framework Cocoa"
                             "-framework IOKit"
                             "-framework CoreVideo"
                             "-framework QuartzCore"
                             ${GLFW_STATIC_LIBRARIES})

set(${PROJECT_NAME}_LIBRARY_DIRS ${PROJECT_SOURCE_DIR}/lib
    CACHE INTERNAL "${PROJECT_NAME}: Library Directories" FORCE)
