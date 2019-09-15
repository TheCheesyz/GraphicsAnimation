#include "GraphicsEngine.h"

void GraphicsEngine::init() {
	VulkanHandler vh;
	GraphicsPipelineHandler gph;
	vh.initWindow();
	vh.initVulkan();
	gph.createGraphicsPipeline();
	vh.mainLoop();
	vh.cleanup();
}