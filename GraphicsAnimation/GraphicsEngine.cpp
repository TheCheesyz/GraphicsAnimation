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
	uint32_t imageIndex;
	vkAcquireNextImageKHR(vh.getDevice(), vh.getSwapChain(), UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &(gph.getCommandBuffers())[imageIndex];

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(vh.getGraphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
		throw std::runtime_error("Unable to submit draw command.");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { vh.getSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;

	presentInfo.pResults = nullptr;

	vkQueuePresentKHR(vh.getPresentQueue(), &presentInfo);
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