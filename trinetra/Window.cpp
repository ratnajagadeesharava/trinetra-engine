#include "Window.h"

Window::Window(int height, int width, string title)
{
	if (!glfwInit()) throw std::runtime_error("Failed to Initialize GLFW");
	const char* windowTitle = title.c_str();
	Handle = glfwCreateWindow(
		width, height, windowTitle, nullptr, nullptr
	);
	if (!Handle) {
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(Handle);
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to Initialize GLEW");
	}
}

Window::~Window()
{

	glfwDestroyWindow(Handle);
	glfwTerminate();
}

int Window::ShouldClose()
{
	return glfwWindowShouldClose(Handle);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(Handle);
}

void Window::PollEvents()
{
	glfwPollEvents();
}
