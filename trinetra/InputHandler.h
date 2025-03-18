#pragma once
#include "typedefs.h"
class InputHandler
{
public:
	static void KeyCallBack(GLFWwindow* window, GLint key, GLint ScanCode, GLint action, GLint mods);
	static bool IsKeyPressed(int key);
	static void ProcessInput(Vector3& cameraPosition, float speed = 0.5f);
	static Vector3 ColorChange(int  key, Vector3 prevColor);
private:
	static bool keys[1024];

};