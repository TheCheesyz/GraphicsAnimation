#ifndef GRAPHICS_PIPELINE
#define GRAPHICS_PIPELINE

#include <fstream>
#include <vector>
#include <vulkan\vulkan_core.h>
#include "VulkanHandler.h"

class GraphicsPipelineHandler
{
public:
	GraphicsPipelineHandler();
	GraphicsPipelineHandler(VulkanHandler* vh_);
	void initGraphicsPipeline();
	void recreateSwapChainGraphicsPipeline();
	void cleanupSwapchainGraphicsPipeline();
	void cleanup();
	std::vector<VkCommandBuffer>& getCommandBuffers();

private:
	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createVertexBuffer();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VulkanHandler* vh;
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
};

#endif