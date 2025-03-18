#include "Camera.h"

Camera::Camera(Vector3 startPosition):position(startPosition),up(0.0f,1.0f,0.0f),front(0,0,-1.0f),speed(1.0f),sensitivity(1.0f),yaw(-90.0f),pitch(0.0f)
{

}

Matrix4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}
void Camera::ProcessKeyboard(int key) {
    if (key == GLFW_KEY_W) position += speed * front;
    if (key == GLFW_KEY_S) position -= speed * front;
    if (key == GLFW_KEY_A) position -= glm::normalize(glm::cross(front, up)) * speed;
    if (key == GLFW_KEY_D) position += glm::normalize(glm::cross(front, up)) * speed;
}
