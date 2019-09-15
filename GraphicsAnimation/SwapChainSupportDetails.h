#ifndef SWAP_CHAIN_SUP
#define SWAP_CHAIN_SUP

#include <vulkan\vulkan_core.h>
#include <vector>

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

#endif