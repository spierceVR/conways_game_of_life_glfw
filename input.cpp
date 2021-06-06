#include "input.h"

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	std::cout << key << std::endl;

	if (key == GLFW_KEY_SPACE) {
		switch (action) {
		case GLFW_PRESS:
			std::cout << "Space key is pressed\n";
			break;
		case GLFW_REPEAT:
			std::cout << "Space key is being held\n";
			break;
		case GLFW_RELEASE:
			std::cout << "Space key has been released\n";
			break;
		default:
			break;
		}
	}
}

void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	std::cout << xPos << " : " << yPos << "\n";
}