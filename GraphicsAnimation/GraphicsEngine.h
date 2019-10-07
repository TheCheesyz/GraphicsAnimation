#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include "VulkanHandler.h"
#include "GraphicsPipelineHandler.h"
#include "ObjLoader.h"

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

	VulkanHandler vh;
	GraphicsPipelineHandler gph;
	ObjLoader ol;
	GLFWwindow* window;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

};

#endif