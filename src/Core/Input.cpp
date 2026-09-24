#include "Input.hpp"

#include <utility>
#include <algorithm>

#include <GLFW/glfw3.h>

bool keys[GLFW_KEY_LAST + 1]; // +1 because seems like GLFW_KEY_LAST is an actual key that can be received from GLFW
float lastFrame, deltaTime;

struct CursorPanCallbackEntry {
    Input::CallbackId id;
    Input::CursorPanCallback callback;
};

std::vector<CursorPanCallbackEntry> cursorPanCallbacks;
Input::CallbackId nextCallbackId = 0;

void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	if (key >= 0 && key <= GLFW_KEY_LAST)
	    keys[key] = action != GLFW_RELEASE;
}

void CursorPositionCallback(GLFWwindow* window, double x, double y) {
	glm::vec2 position = { x, y };
	for (auto& entry : cursorPanCallbacks)
		entry.callback(position);
}

void Input::Init(GLFWwindow* native) {
    lastFrame = static_cast<float>(glfwGetTime());

	glfwSetKeyCallback(native, KeyCallback);
	glfwSetCursorPosCallback(native, CursorPositionCallback);
}

void Input::Update() {
	auto currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

Input::CallbackId Input::AddCursorPanCallback(CursorPanCallback callback) {
    const auto id = nextCallbackId++;
	cursorPanCallbacks.emplace_back(id, std::move(callback));
	return id;
}

void Input::RemoveCursorPanCallback(CallbackId id) {
    std::erase_if(cursorPanCallbacks, [id](const CursorPanCallbackEntry& entry) { return entry.id == id; });
}

bool Input::IsKeyHeld(Key key) {
	return keys[static_cast<int>(key)] != GLFW_RELEASE;
}

float Input::GetDeltaTime() {
	return deltaTime;
}

float Input::GetElapsedTime() {
	return glfwGetTime();
}
