/**
*
*	Zephram Carroll 12_16_2019
*	
*	Using Vulkan API generates an animal and sets it running.
*
*	Initial Vulkan setup and education performed using the tutorial at: https://vulkan-tutorial.com/
*
*/

#include "GraphicsEngine.h"

int main() {

	GraphicsEngine ge;
	try {
		ge.init();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}