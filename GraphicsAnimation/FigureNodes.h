#ifndef FIGURE_NODES
#define FIGURE_NODES

#include <glm/glm.hpp>
#include <vector>
#include <memory>

typedef struct FigureNodes {
	glm::vec3 pos;
	glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f);
	bool gravity = false;
	std::vector<FigureNodes*> children;
	FigureNodes* parent;
} Node;

#endif