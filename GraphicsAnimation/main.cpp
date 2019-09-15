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