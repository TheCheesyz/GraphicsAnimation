#ifndef OBJ_LOADER
#define OBJ_LOADER

#include <string>
#include <unordered_map>
#include <tiny_obj_loader.h>
#include "Vertex.h"

class ObjLoader {
public:
	void loadModel(std::string modelPath);
	std::vector<Vertex> getVertices();
	std::vector<uint32_t> getIndices();
private:

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};

#endif