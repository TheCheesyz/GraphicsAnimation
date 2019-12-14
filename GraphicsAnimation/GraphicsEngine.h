#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "VulkanHandler.h"
#include "GraphicsPipelineHandler.h"
#include "ObjLoader.h"
#include "FigureNodes.h"
#include "PhysicsEngine.h"

class GraphicsEngine
{
public:
	void init();

private:
	void mainLoop();
	void drawFrame();
	void createSyncObjects();
	void recreateSwapChain();
	void updateUniformBuffer(uint32_t currentImage);
	void cleanupSwapChain();
	void cleanup();

	void createFigure();
	void figureUpdate(FigureNodes& node, uint32_t currentImage, float time);

	VulkanHandler vh;
	GraphicsPipelineHandler gph;
	ObjLoader ol;
	GLFWwindow* window;
	PhysicsEngine pe;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

	FigureNodes root;
	uint32_t nodeIterator;
};

#endif