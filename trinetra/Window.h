#pragma once
#include "typedefs.h"
class Window
{
public:
	GLFWwindow* Handle;

	Window(int height, int width, string title);

	~Window();
	
	int ShouldClose();

	void SwapBuffers();
	void PollEvents();
protected:
	int height, width;
	string title;
};

