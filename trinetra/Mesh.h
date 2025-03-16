#pragma once
#include "typedefs.h"
class Mesh
{
public:
	GLuint  VAO, VBO,NBO;


	Mesh(const vector<Vector3>& vert,const vector<Vector3> normals,GLuint ShaderProgramId);

	void Draw();

	~Mesh();
protected:
	GLuint ShaderId;
	int verticesSize;
};

