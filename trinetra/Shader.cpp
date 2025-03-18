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
	GLint success;
	glGetProgramiv(ProgramId, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetProgramInfoLog(ProgramId, 1024, nullptr, infoLog);
		std::cerr << "Shader Linking Failed:\n" << infoLog << endl;
	}
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
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		const string shaderName = shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader";
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader Compilation Failed:\n" << shaderName << "  --> " << infoLog << endl;
	}
	return shader;
}

Shader::~Shader()
{
}
