#include "InputHandler.h"

bool InputHandler::keys[1024] = { false };
void InputHandler::KeyCallBack(GLFWwindow* window, GLint key, GLint ScanCode, GLint action, GLint mods)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, true);
	}
	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

bool InputHandler::IsKeyPressed(int key)
{
	return keys[key];
}

void InputHandler::ProcessInput(Vector3& cameraPosition, float speed)
{
	if (IsKeyPressed(GLFW_KEY_W)) {
		cameraPosition.z += speed;
		cout << "GLFW_KEY_W" << endl;
	}
	if (IsKeyPressed(GLFW_KEY_S))cameraPosition.z -= speed;
	if (IsKeyPressed(GLFW_KEY_A))cameraPosition.x -= speed;
	if (IsKeyPressed(GLFW_KEY_D))cameraPosition.x += speed;
}

Vector3 InputHandler::ColorChange(int key, Vector3 prevColor)
{
	std::vector<Vector3> diffColors = {
	Vector3(0.5f, 0.5f, 0.9f),
	Vector3(0.9f, 0.5f, 0.5f),
	Vector3(0.5f, 0.9f, 0.3f),
	Vector3(0.3f, 0.8f, 0.9f),
	Vector3(0.4f, 0.3f, 0.3f)
	};
	Vector3 result = prevColor;
	if (IsKeyPressed(GLFW_KEY_C))
	{
		result = diffColors[(rand() % 4) + 1];
	}
	return result;

}