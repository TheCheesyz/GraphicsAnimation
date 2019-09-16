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
	void createSemaphores();
	void cleanup();

	VulkanHandler vh;
	GraphicsPipelineHandler gph;
	GLFWwindow* window;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
};

#endif