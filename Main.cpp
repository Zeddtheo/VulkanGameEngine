#include "FirstApp.h"
#include <iostream>

int main() {
	misc::FirstApp app{};
	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}