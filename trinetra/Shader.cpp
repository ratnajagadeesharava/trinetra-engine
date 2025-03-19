#include "Shader.h"

Shader::Shader(const string& vertexShaderPath, const string& fragmentShaderPath)
{
	string vertexShaderSrc = readFile(vertexShaderPath);
	string  fragmentShaderSrc = readFile(fragmentShaderPath);
	VertexShader = CompileShader(vertexShaderSrc, GL_VERTEX_SHADER);
	FragmentShader = CompileShader(fragmentShaderSrc, GL_FRAGMENT_SHADER);
	CreateShaderProgram();
}

void Shader::CreateShaderProgram()
{
	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShader);
	glAttachShader(ProgramId, FragmentShader);
	glLinkProgram(ProgramId);
	glValidateProgram(ProgramId);
	glDetachShader(ProgramId, VertexShader);
	glDetachShader(ProgramId, FragmentShader);
}

GLuint Shader::CompileShader(string& shaderSrc, GLuint shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	const char* srcCode = shaderSrc.c_str();
	glShaderSource(shader, 1, &srcCode, nullptr);
	glCompileShader(shader);
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS,&success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader Compilation Failed:\n" << infoLog << endl;
	}
	return shader;
}
