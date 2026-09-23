cmake_minimum_required(VERSION 3.21)
project(opengl_3d_engine)

set(CMAKE_CXX_STANDARD 23)

add_executable(opengl_3d_engine src/Main.cpp src/Core/Window.cpp src/Core/Shaders.cpp src/Debug/Log.cpp src/Core/Camera.cpp src/Core/Entity.cpp src/Core/Model.cpp src/Core/Renderer.cpp src/Core/Input.cpp src/Core/Texture.cpp src/Core/Terrain.cpp src/Core/Terrain.hpp)

# deps
add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/assimp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_ASSIMP_VIEW OFF)

add_compile_definitions(GLFW_INCLUDE_NONE)

# linking
target_precompile_headers(opengl_3d_engine PRIVATE <memory> <string_view>)
target_include_directories(opengl_3d_engine PRIVATE deps/glm deps/stb)
target_link_libraries(opengl_3d_engine PRIVATE glfw glad spdlog::spdlog assimp)

# post-build
add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)
add_dependencies(opengl_3d_engine copy_assets)
