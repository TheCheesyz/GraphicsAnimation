#ifndef GRAPHICS_PIPELINE
#define GRAPHICS_PIPELINE

#include <fstream>
#include <vector>
#include <vulkan\vulkan_core.h>
#include "QueueFamilyIndices.h"

class GraphicsPipelineHandler
{
public:
	GraphicsPipelineHandler();
	GraphicsPipelineHandler(VkDevice pdevice, VkExtent2D pswapChainExtent, VkFormat pswapChainImageFormat, std::vector<VkImageView> pswapChainImageViews, QueueFamilyIndices pqueueFamilyIndices);
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void cleanup();
	std::vector<VkCommandBuffer>& getCommandBuffers();

private:
	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkDevice device;
	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkImageView> swapChainImageViews;
	VkCommandPool commandPool;
	QueueFamilyIndices queueFamilyIndices;
	std::vector<VkCommandBuffer> commandBuffers;
};

#endif