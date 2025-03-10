#include "ModelLoader.h"

void ModelLoader::loadFromFile(const char* path)
{
    std::ifstream file(path);
    string line;
    while (getline(file, line)) {
        FormatObjectLine(line);
    }
}

void ModelLoader::FormatObjectLine(string& line)
{
    switch (line[0]) {
    case 'v':
        if (line[1] == 'n') {
            line.erase(0, 3);
            float x, y, z;
            std::istringstream(line) >> x >> y >> z;
            normals.push_back(glm::vec3(x, y, z));
        }
        else {
            line.erase(0, 2);
            float x, y, z;
            std::istringstream(line) >> x >> y >> z;
            vertices.push_back(glm::vec3(x, y, z));
        }
        break;
    case 'f':
        line.erase(0, 2);
        stringstream ss(line);
        string token;
        vector<unsigned> result;
        while (getline(ss, token, ' ')) {
            std::stringstream ssToken(token);
            std::string numStr;
            while (std::getline(ssToken, numStr, '/')) { // Split by '/'
                result.push_back(std::stoi(numStr));
                //cout << numStr<<endl;
            }
        }
        faces.push_back(result);
        break;
    };
}
