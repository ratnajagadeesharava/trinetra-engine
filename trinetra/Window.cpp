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
	glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
	//glEnable(GL_LIGHTING);     // Enable lfighting calculations
	//glEnable(GL_LIGHT0);       // Turn on light #0.
	//glfwGetFramebufferSize(Handle, &width, &height);
	glViewport(0, 0, width, height);
	//std::cout << "Viewport set to: " << width << "x" << height << std::endl;
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
