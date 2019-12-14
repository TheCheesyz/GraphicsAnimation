#ifndef PHYSICS
#define PHYSICS

#include <glm/glm.hpp>
#include "FigureNodes.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	PhysicsEngine(glm::vec3 gravity_, float floor_);
	void applyPhysics(FigureNodes& node, float deltaTime);

private:
	bool checkFloorCollision(float yPos);
	void applyForces(FigureNodes& node, float deltaTime);
	void applyVelocity(FigureNodes& node, float deltaTime);

	glm::vec3 gravity;
	float floor;
};

#endif