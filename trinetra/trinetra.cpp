#include "typedefs.h"
#include <filesystem>
#include "Shader.h"
#include "Mesh.h"
#include "Window.h"
#include "ModelLoader.h"

void prepareActualVertices();

string vertexPath = ".\\src\\shaders\\VertexShader.shader";
string fragmentpath = ".\\src\\shaders\\FragmentShader.shader";
vector<glm::vec3> AllVertices;
// Vertex data for a simple triangle with alternating colors
vector<float> vertexData = {
    // Position       // Color (R, G, B)
    -0.8f,  0.8f, 0.0f,  1.0f, 0.0f, 0.0f,  // Vertex 1 (Red)
    -0.8f, -0.8f, 0.0f,  0.0f, 1.0f, 0.0f,  // Vertex 2 (Green)
     0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,  // Vertex 3 (Blue)
     0.8f, -0.8f, 0.0f,  0.0f, 0.0f, 1.0f,  // Vertex 3 (Blue)
     0.8f,  0.8f, 0.0f,  0.0f, 1.0f, 1.0f,  // Vertex 4 (Cyan)
    -0.8f,  0.8f, 0.0f,  1.0f, 0.0f, 0.0f   // Vertex 1 (Red)
};
std::vector<glm::vec3> vertices = {
    // Vertex A
    glm::vec3(-0.5f, -0.5f, 0.0f), // Bottom-left vertex
    glm::vec3(0.0f, 1.0f, 0.0f),   // Green color
    // Vertex B
    glm::vec3(0.5f, -0.5f, 0.0f),  // Bottom-right vertex
    glm::vec3(0.0f, 0.0f, 1.0f),   // Blue color
    // Vertex C
    glm::vec3(0.5f, 0.5f, 0.0f),   // Top-right vertex
    glm::vec3(1.0f, 0.0f, 0.0f),   // Red color
    // Vertex D
    glm::vec3(-0.5f, 0.5f, 0.0f),  // Top-left vertex
    glm::vec3(1.0f, 1.0f, 0.0f),   // Yellow color
    // Vertex A
    glm::vec3(-0.5f, -0.5f, 0.0f), // Bottom-left vertex
    glm::vec3(0.0f, 1.0f, 0.0f),   // Green color
    // Vertex C
    glm::vec3(0.5f, 0.5f, 0.0f),   // Top-right vertex
    glm::vec3(1.0f, 0.0f, 0.0f)    // Red color
};


void HandleInput(GLFWwindow *window,GLint key,GLint ScanCode, GLint action, GLint mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    
    Window window(1080, 1920, "Trinetra Engine");
    Shader shader(vertexPath, fragmentpath);
    ModelLoader model;
    model.loadFromFile(".\\garg.obj");
    prepareActualVertices(model);
    Mesh garg(AllVertices, shader.ProgramId);
    glfwSetKeyCallback(window.Handle, HandleInput);
    while (!(window.ShouldClose())) {
        glClear(GL_COLOR_BUFFER_BIT);
        garg.Draw();
        window.SwapBuffers();
        window.PollEvents();
    }
    return 0;
}
// without using EBO
void prepareActualVertices(ModelLoader& model) {
    int n = model.faces.size();
    for (vector<unsigned> v : model.faces) {
        unsigned a = v[0], d = v[3], g = v[6];
        unsigned c = v[2], f = v[5], i = v[8];
        vector<Vector3> ObjVertices = model.vertices;
        AllVertices.push_back(ObjVertices[a - 1]);
        AllVertices.push_back(ObjVertices[d - 1]);
        AllVertices.push_back(ObjVertices[g - 1]);
    }
}
