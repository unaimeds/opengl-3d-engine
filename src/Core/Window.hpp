#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct GLFWwindow;

class Window {
public:
	Window(std::string_view title, const glm::uvec2& size);
	~Window();

	bool IsOpen() const;

	const glm::uvec2& GetSize() const { return size; }
	GLFWwindow* GetNative() const { return _window; }

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	GLFWwindow* _window;
	glm::uvec2 size;
};
