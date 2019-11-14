#ifndef RENDERED
#define RENDERED

#include <vulkan\vulkan_core.h>
#include "UniformBufferObject.h"


struct RenderedObject {
	UniformBufferObject ubo;
	std::vector<VkDescriptorSet> descriptorSets;
	//VkDescriptorSet descriptorSet;
	std::vector<VkBuffer> uniformBuffers;
	//VkBuffer uniformBuffer;
};

#endif