#include "GraphicsEngine.h"

const int MAX_FRAMES_IN_FLIGHT = 2;

void GraphicsEngine::init() {
	vh = VulkanHandler();
	window = vh.initWindow();
	vh.initVulkan();
	gph = GraphicsPipelineHandler(&vh);
	gph.initGraphicsPipeline();
	createSyncObjects();
	mainLoop();
	cleanup();
}

void GraphicsEngine::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		drawFrame();
	}

	vkDeviceWaitIdle(vh.getDevice());
}

void GraphicsEngine::drawFrame() {
	vkWaitForFences(vh.getDevice(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);
	
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(vh.getDevice(), vh.getSwapChain(), UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("Unable to acquire image for the swap chain.");
	}

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &(gph.getCommandBuffers())[imageIndex];

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(vh.getDevice(), 1, &inFlightFences[currentFrame]);

	if (vkQueueSubmit(vh.getGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
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

	result = vkQueuePresentKHR(vh.getPresentQueue(), &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || vh.getFramebufferResized()) {
		vh.setFramebufferResized(false);
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("Unable to present image from swapchain.");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void GraphicsEngine::createSyncObjects() {
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++){
		if (vkCreateSemaphore(vh.getDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(vh.getDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(vh.getDevice(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("Unable to create sync objects.");
		}
	}
}

void GraphicsEngine::recreateSwapChain() {
	int width = 0, height = 0;
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(vh.getDevice());

	cleanupSwapChain();

	vh.recreateSwapChainVulkan();
	gph.recreateSwapChainGraphicsPipeline();
}

void GraphicsEngine::cleanupSwapChain() {
	gph.cleanupSwapchainGraphicsPipeline();
	vh.cleanupSwapChainVulkan();
}

void GraphicsEngine::cleanup() {
	cleanupSwapChain();

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(vh.getDevice(), renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(vh.getDevice(), imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(vh.getDevice(), inFlightFences[i], nullptr);
	}

	gph.cleanup();
	vh.cleanup();
}