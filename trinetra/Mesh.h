#pragma once
#include "typedefs.h"
class Mesh
{
public:
	GLuint  VAO, VBO;


	Mesh(const vector<Vector3> vert,GLuint ShaderProgramId);

	void Draw();

	~Mesh();
protected:
	GLuint ShaderId;
	bool IsColor;
	int verticesSize;
};

