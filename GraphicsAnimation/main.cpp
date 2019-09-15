#include "MakingTriangle.h"

int main() {

	MakingTriangle tri;
	try {
		tri.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}