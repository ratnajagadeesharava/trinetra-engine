#include "typedefs.h"
#include <filesystem>
#include "Shader.h"
#include "Mesh.h"
#include "Window.h"
#include "ModelLoader.h"

#include "InputHandler.h"
#include "Camera.h"
void prepareActualVertices(ModelLoader& model);

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
vector<glm::vec3> Vertices;
vector<glm::vec3> Normals;
const int Height = 1080;
const int Width = 1920;
const float aspectRatio = float(Width) / float(Height);
Camera camera(Vector3(0.0f, 0.0f, 3.0f));
void HandleInput(GLFWwindow* window, GLint key, GLint ScanCode, GLint action, GLint mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        camera.ProcessKeyboard(key);
    }
}

Matrix4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

//void getUniformLocation()
int main() {
    
    Window window(1080, 1920, "Trinetra Engine");
    //window.cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 lightColor(0.4f, .5f, 1.0f);
    glm::vec3 objectColor(0.8f, 0.1f, 0.6f);
    glm::vec3 viewPos = window.cameraPos;
    Shader shader(vertexPath, fragmentpath);
    //GLuint lightPosLoc, lightColorLoc, objectColorLoc, viewPosLoc;
    GLuint lightPosLoc = glGetUniformLocation(shader.ProgramId, "lightPos");
    GLuint lightColorLoc = glGetUniformLocation(shader.ProgramId, "lightColor");
    GLuint objectColorLoc = glGetUniformLocation(shader.ProgramId, "objectColor");
    GLuint viewPosLoc = glGetUniformLocation(shader.ProgramId, "viewPos");
    GLuint projectionLocation = glGetUniformLocation(shader.ProgramId, "projection");
    GLuint viewMatrixLocation = glGetUniformLocation(shader.ProgramId, "viewMatrix");
    
    Matrix4 modelmat = glm::scale(glm::mat4(1.0f), glm::vec3(0.02f));
    GLuint modelMatLocation = glGetUniformLocation(shader.ProgramId, "model");
    ModelLoader model ;
    model.loadFromFile(".\\garg.obj");
    prepareActualVertices(model);
    Mesh garg(Vertices,Normals, shader.ProgramId);
    glfwSetKeyCallback(window.Handle, HandleInput);
    glEnable(GL_DEPTH_TEST);
    /*Matrix4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)); */
    while (!(window.ShouldClose())) {
      
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewPos));
        glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, glm::value_ptr(modelmat));
        cout << camera.position.x<<" "<<camera.position.y<<" "<<camera.position.z << endl;
        glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));
        InputHandler::ProcessInput(window.cameraPos);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        vector<Vector3> ObjNormals = model.normals;
        Vertices.push_back(ObjVertices[a - 1]);
        Vertices.push_back(ObjVertices[d - 1]);
        Vertices.push_back(ObjVertices[g - 1]);
        Normals.push_back(ObjNormals[a - 1]);
        Normals.push_back(ObjNormals[d - 1]);
        Normals.push_back(ObjNormals[g - 1]);
    }
}
