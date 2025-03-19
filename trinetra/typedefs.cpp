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


 void GlClearAllErrors() {
    while (glGetError() != GL_NO_ERROR) {}
}

