#include "GraphicsEngine.h"

void GraphicsEngine::init() {
	vh = VulkanHandler();
	window = vh.initWindow();
	vh.initVulkan();
	gph = GraphicsPipelineHandler(vh.getDevice(), vh.getSwapchainExtent(), vh.getSwapchainFormat(), vh.getSwapChainImageViews(), vh.findQueueFamilies(vh.getPhysicalDevice()));
	gph.createRenderPass();
	gph.createGraphicsPipeline();
	gph.createFramebuffers();
	gph.createCommandPool();
	gph.createCommandBuffers();
	createSemaphores();
	mainLoop();
	cleanup();
	gph.cleanup();
	vh.cleanup();
}

void GraphicsEngine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
	}
}

void GraphicsEngine::drawFrame() {

}

void GraphicsEngine::createSemaphores() {
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if (vkCreateSemaphore(vh.getDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
		vkCreateSemaphore(vh.getDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {
		throw std::runtime_error("Unable to create semaphores.");
	}
}

void GraphicsEngine::cleanup() {
	vkDestroySemaphore(vh.getDevice(), renderFinishedSemaphore, nullptr);
	vkDestroySemaphore(vh.getDevice(), imageAvailableSemaphore, nullptr);
}