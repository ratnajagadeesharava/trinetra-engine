#include "Mesh.h"

void Mesh::Draw()
{
	glUseProgram(ShaderId);
	glDrawArrays(GL_TRIANGLES, 0, verticesSize);
}



Mesh::Mesh(const vector<Vector3>& vertices, const vector<Vector3> normals, GLuint ShaderProgramId) :ShaderId(ShaderProgramId), verticesSize(vertices.size())
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vector3),
		vertices.data(),
		GL_STATIC_DRAW
	);
	//enable vertex array for vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		normals.size() * sizeof(Vector3),
		normals.data(), GL_STATIC_DRAW
	);
	//enable vertex array for colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &NBO);
}