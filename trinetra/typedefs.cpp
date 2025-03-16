#include "typedefs.h"
string readFile(const string& fileName) {
    std::ifstream file(fileName);
    stringstream ss;
    string line;
    while (getline(file, line)) {
        ss << line << endl;
    }
    return ss.str();
}

 bool GLCheckErrorStatus(const char* function, int line) {
    while (GLenum error = glGetError()) {
        cout << "OPENGL Error:" << error << "\t line: " << line << "\t function" << function << endl;
        return true;
    }
    return false;
}

 void CheckOpenGLError(const char* file, const char* function, int line)
 {
     GLenum error;
     while ((error = glGetError()) != GL_NO_ERROR)
     {
         std::cerr << "[OpenGL ERROR] (" << error << ") in "
             << file << " -> " << function
             << " at line " << line << endl;
     }
 }


 void GlClearAllErrors() {
    while (glGetError() != GL_NO_ERROR) {}
}

