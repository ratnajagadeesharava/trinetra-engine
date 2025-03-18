#pragma once
#include "typedefs.h"
class Window
{
public:
	GLFWwindow* Handle;
	Vector3 cameraPos = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 target = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 upVector = Vector3(0.0, 1.0, 0.0f);
	Window(int height, int width, string title);

	~Window();
	
	int ShouldClose();

	void SwapBuffers();
	void PollEvents();
protected:
	int height, width;
	string title;
};

