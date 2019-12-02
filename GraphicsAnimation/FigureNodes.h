#ifndef FIGURE_NODES
#define FIGURE_NODES

#include <glm/glm.hpp>
#include <vector>
#include <memory>

typedef struct FigureNodes {
	glm::vec3 pos;
	std::vector<FigureNodes> children;
	std::shared_ptr<FigureNodes> parent;
} Node;

#endif