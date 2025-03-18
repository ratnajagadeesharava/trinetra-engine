#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <fstream>


#define endl std::endl
#define cout std::cout

//Both typedef and using are used to create type aliases, but they have key differences in syntax and flexibility

template<typename T>
using vector = std::vector<T>;

typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::vec2 Vector2;
typedef glm::mat4 Matrix4;

typedef std::string string;
typedef std::stringstream stringstream;

 void GlClearAllErrors();

 bool GLCheckErrorStatus(const char* function, int line);
 void CheckOpenGLError(const char* file, const char* function, int line);


#define GLCheck(x) do { \
    x; \
    CheckOpenGLError(__FILE__,#x, __LINE__); \
} while(0)

string readFile(const string& fileName);
