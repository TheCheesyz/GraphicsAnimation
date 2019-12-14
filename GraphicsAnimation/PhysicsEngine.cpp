#include "PhysicsEngine.h"
#include <iostream> //deleteme
PhysicsEngine::PhysicsEngine() {

}

PhysicsEngine::PhysicsEngine(glm::vec3 gravity_, float floor_) :
	gravity(gravity_), floor(floor_) {

}

void PhysicsEngine::applyPhysics(FigureNodes& node, float deltaTime) {
	applyForces(node, deltaTime);
	applyVelocity(node, deltaTime);
}

bool PhysicsEngine::checkFloorCollision(float yPos) {
	if (yPos > floor) {
		return true;
	}
	return false;
}

void PhysicsEngine::applyForces(FigureNodes& node, float deltaTime) {
	node.vel += (gravity * deltaTime);
	if (checkFloorCollision(node.pos.y)) {
		if(node.vel.y > 0)
			node.vel.y *= -1;
		node.vel -= (gravity * deltaTime);
	}
}

void PhysicsEngine::applyVelocity(FigureNodes& node, float deltaTime) {
	node.pos += (node.vel * deltaTime);
}

