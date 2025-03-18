#pragma once
#include "typedefs.h"
class Camera
{
public:
	Vector3 position;
	Vector3 front;
	Vector3 up;
	float speed,sensitivity,yaw,pitch;
	Camera(Vector3 startPosition);
	Matrix4 GetViewMatrix();
	void ProcessKeyboard(int key);
	//void ProcessMouse(float xOffset, float yOffset);
};

