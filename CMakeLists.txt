cmake_minimum_required(VERSION 3.20)

project(opengl_3d_engine VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)


# Dependencies configuration
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MMD_IMPORTER OFF CACHE BOOL "" FORCE)


# Dependencies
add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/assimp)


add_executable(
    opengl_3d_engine

    src/Main.cpp

    src/Core/Window.cpp src/Core/Shaders.cpp src/Core/Camera.cpp
    src/Core/Entity.cpp src/Core/Model.cpp src/Core/Renderer.cpp
    src/Core/Input.cpp src/Core/Texture.cpp src/Core/Terrain.cpp

    src/Debug/Log.cpp
)


# Compiler config, includes, and linking
add_compile_definitions(GLFW_INCLUDE_NONE)

target_precompile_headers(opengl_3d_engine PRIVATE <memory> <string_view>)

target_include_directories(opengl_3d_engine PRIVATE deps/glm deps/stb)

target_link_libraries(opengl_3d_engine PRIVATE glfw glad spdlog::spdlog assimp)


# Copy assets to output directory after compiling the project
add_custom_target(
    copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(opengl_3d_engine copy_assets)
