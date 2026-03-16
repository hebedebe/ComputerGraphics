#include "ComputerGraphicsApp.h"

int main() {
	
	// allocation
	auto app = ComputerGraphicsApp::Get();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}