#pragma once
#include "typedefs.h"
class ModelLoader
{
public:
	vector<Vector3> vertices, normals;
	vector<vector<unsigned>> faces;
	void loadFromFile(const char*);
	void FormatObjectLine(string& line);
};

