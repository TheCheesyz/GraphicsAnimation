#ifndef GRAPHICS_PIPELINE
#define GRAPHICS_PIPELINE

#include <fstream>
#include <vector>
#include <vulkan\vulkan_core.h>
#include "VulkanHandler.h"
#include "Vertex.h"
#include "UniformBufferObject.h"

class GraphicsPipelineHandler
{
public:
	GraphicsPipelineHandler();
	GraphicsPipelineHandler(VulkanHandler* vh_);
	void initGraphicsPipeline();
	void recreateSwapChainGraphicsPipeline();
	void cleanupSwapchainGraphicsPipeline();
	void cleanup();
	std::vector<VkDeviceMemory>& getUniformBuffersMemory();
	std::vector<VkCommandBuffer>& getCommandBuffers();

private:
	std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createRenderPass();
	void createDescriptorSetLayout();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
	void createDescriptorPool();
	void createDescriptorSets();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VulkanHandler* vh;
	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;
};

#endif