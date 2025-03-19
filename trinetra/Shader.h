#pragma once
#include "typedefs.h"
class Shader
{
	
public:
	GLuint ProgramId;
	Shader(const string& vertexShaderPath,const string& fragmentShaderPath);
	
private:
	void CreateShaderProgram();
	GLuint CompileShader(string& shaderSrc,GLuint shaderType);
	GLuint  VertexShader;
	GLuint FragmentShader;
	
};

