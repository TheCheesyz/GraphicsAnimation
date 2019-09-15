#include "GraphicsEngine.h"

void GraphicsEngine::init() {
	VulkanHandler vh;
	vh.run();
	GraphicsPipelineHandler gph;
	gph.createGraphicsPipeline();
}