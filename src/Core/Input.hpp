#pragma once

#include <functional>

#include <glm/vec2.hpp>

enum class Key {
	W = 87,
	S = 83,
	A = 65,
	D = 68,

	Shift = 340, // left shift
};

struct GLFWwindow;

namespace Input {
	using CursorPanCallback = std::function<void(glm::vec2)>;
	using CallbackId = std::uint64_t;

	void Init(GLFWwindow* native);
	void Update();

	CallbackId AddCursorPanCallback(CursorPanCallback callback);
	void RemoveCursorPanCallback(CallbackId id);

	bool IsKeyHeld(Key key);
	float GetDeltaTime();
	float GetElapsedTime();
}
