#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE

#include "VulkanHandler.h"
#include "GraphicsPipelineHandler.h"

class GraphicsEngine
{
public:
	void init();

private:
	void mainLoop();
	void drawFrame();
	void createSyncObjects();
	void recreateSwapChain();
	void cleanupSwapChain();
	void cleanup();

	VulkanHandler vh;
	GraphicsPipelineHandler gph;
	GLFWwindow* window;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

};

#endif