#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() {

}

PhysicsEngine::PhysicsEngine(glm::vec3 gravity_, float floor_) :
	gravity(gravity_), floor(floor_) {

}

void PhysicsEngine::applyPhysics(FigureNodes* node, float deltaTime) {
	if (node->gravity == true) {
		applyForces(node, deltaTime);
	}
	applyVelocity(node, deltaTime);
	if (node->gravity == true) {
		adjustParent(node);
	}
}

void PhysicsEngine::applyAcceleration(FigureNodes* root) {
	for (auto child : root->children) {
		applyAcceleration(child);
	}
	if (accelerate) {
		root->vel.x -= .2;
		if(root->parent == NULL)
			accelerate = false;
	}
	else {
		if (root->vel.x < 0) {
			root->vel.x += .005;
		}
	}
}

bool PhysicsEngine::checkFloorCollision(float yPos) {
	if (yPos >= floor) {
		return true;
	}
	return false;
}

void PhysicsEngine::applyForces(FigureNodes* node, float deltaTime) {
	node->vel += (gravity * deltaTime);
	if (checkFloorCollision(node->pos.y)) {
		if(node->vel.y > 0)
			node->vel.y *= -1;
		accelerate = true;
	}
}

void PhysicsEngine::applyVelocity(FigureNodes* node, float deltaTime) {
	node->pos += (node->vel * deltaTime);
}

void PhysicsEngine::adjustParent(FigureNodes* node) {
	node->parent->pos.y = node->pos.y - 1;
	node->parent->pos.x = -sqrt(1 - pow(node->parent->pos.y, 2)) + node->parent->parent->pos.x;
	node->pos.x = node->parent->pos.x;
}

