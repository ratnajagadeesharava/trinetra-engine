#include "Mesh.h"

Mesh::Mesh(const vector<Vector3>& vertices, const vector<Vector3> normals, GLuint ShaderProgramId) :ShaderId(ShaderProgramId), verticesSize(vertices.size())
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//generate buffers
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vector3),
		vertices.data(),
		GL_STATIC_DRAW
	);
	glEnableVertexAttribArray(0);
	//const int stride =sizeof(Vector3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);

	// create normal buffers
	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vector3), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glBindVertexArray(0);
	cout << "Mesh Created: " << vertices.size() << " vertices" << endl;

}

void Mesh::Draw()
{
	//cout << "Shader ID in Mesh::Draw(): " << ShaderId << endl;
	GLint currentProgram = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
	//cout << "Current Shader: " << currentProgram << ", Trying to use Shader: " << ShaderId << endl;
	glUseProgram(ShaderId);
	//cout << "VAO: " << VAO << ", VBO: " << VBO << ", verticesSize: " << verticesSize << endl;
	const int vSize =  verticesSize;

	cout << vSize << endl;
	glDrawArrays(GL_TRIANGLES, 0, vSize);
	if (VAO == 0) {
		std::cerr << "VAO is 0! Mesh not set up correctly." << endl;
	}
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &NBO);
}