#include "typedefs.h"
#include <filesystem>
#include "Shader.h"
#include "Mesh.h"
#include "Window.h"
#include "ModelLoader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "InputHandler.h"
void prepareActualVertices(ModelLoader&);

void APIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam)
{
    std::cerr << "OpenGL Debug Message (" << id << "): " << message << endl;

    if (severity == GL_DEBUG_SEVERITY_HIGH) {
        std::cerr << "SEVERITY: HIGH - Critical OpenGL Error!" << endl;
    }
    else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
        std::cerr << "SEVERITY: MEDIUM - Warning!" << endl;
    }
    else if (severity == GL_DEBUG_SEVERITY_LOW) {
        std::cerr << "SEVERITY: LOW - Minor Issue." << endl;
    }
    else {
        std::cerr << "SEVERITY: NOTIFICATION - General Debug Info." << endl;
    }
}

void EnableOpenGLDebug()
{
    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLDebugCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}

string vertexPath = ".\\src\\shaders\\VertexShader.shader";
string fragmentpath = ".\\src\\shaders\\FragmentShader.shader";
vector<Vector3> Vertices;
vector<Vector3> Normals;

const int Height = 1080;
const int Width = 1920;
const float aspectRatio = float(Width)/ float(Height);


//cout<<aspectRatio<<endl;

Matrix4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

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



int main() {
    Window window(1080, 1920, "Trinetra Engine");
    EnableOpenGLDebug();
    window.cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(1.0f, 0.8f, 1.0f);
    glm::vec3 objectColor(0.6f, 0.6f, 0.6f);
    glm::vec3 viewPos = window.cameraPos;

    Vector3 color(0.5f, 0.5f, 0.9f);
    Matrix4 viewMatrix = glm::lookAt(window.cameraPos, window.target, window.upVector);
    Shader shader(vertexPath, fragmentpath);

    GLuint lightPosLoc = glGetUniformLocation(shader.ProgramId, "lightPos");
    GLuint lightColorLoc = glGetUniformLocation(shader.ProgramId, "lightColor");
    GLuint objectColorLoc = glGetUniformLocation(shader.ProgramId, "objectColor");
    GLuint viewPosLoc = glGetUniformLocation(shader.ProgramId, "viewPos");


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLuint projectionLocation = glGetUniformLocation(shader.ProgramId, "projection");
    GLuint viewMatrixLocation = glGetUniformLocation(shader.ProgramId, "viewMatrix");
    Matrix4 modelmat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, -3.0f));// Identity matrix for now
    GLuint modelMatLocation = glGetUniformLocation(shader.ProgramId, "model");
   ModelLoader model;
    model.loadFromFile(".\\garg.obj");
    prepareActualVertices(model);
    Mesh garg(Vertices,Normals, shader.ProgramId);
    //Mesh quad(vertices,N/ormals shader.ProgramId,true);
   

    //glDisable(GL_DEPTH_TEST);
    cout << "Loaded Vertices: " << Vertices.size() << endl;
    cout << "Loaded Normals: " << Normals.size() << endl;
    //cout << "Loaded Faces: " << faces.size() << endl;

    GLCheck(glfwSetKeyCallback(window.Handle, InputHandler::KeyCallBack));
    while (!(window.ShouldClose())) {
        // ensure depth testing correctly
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       /* InputHandler::ProcessInput(window
            .cameraPos);
   
       color = InputHandler::ColorChange(GLFW_KEY_C, color);*/
        /*glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, -0.5f, -1.0f);
        glVertex3f(0.5f, -0.5f, -1.0f);
        glVertex3f(0.0f, 0.5f, -1.0f);
        glEnd();*/
        viewMatrix = glm::lookAt(window.cameraPos, window.target, window.upVector);
        garg.Draw();
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));
        glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, glm::value_ptr(modelmat));
        //cout << "Model Matrix: " << glm::to_string(modelmat) <<endl;
        
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        //quad.Draw();
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
        vector<Vector3> ObjNormals = model.normals;
        Vertices.push_back(ObjVertices[a - 1]);
        Vertices.push_back(ObjVertices[d - 1]);
        Vertices.push_back(ObjVertices[g - 1]);
        Normals.push_back(ObjNormals[a - 1]);
        Normals.push_back(ObjNormals[d - 1]);
        Normals.push_back(ObjNormals[g - 1]);
    }
    
}
