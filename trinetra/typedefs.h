#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>


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


#define GLCheck(x) do { \
    GlClearAllErrors(); \
    x; \
    if (GLCheckErrorStatus(#x, __LINE__)) { \
        std::cerr << "OpenGL Error detected in function: " << #x << " at line " << __LINE__ << endl; \
    } \
} while(0)


string readFile(const string& fileName);
