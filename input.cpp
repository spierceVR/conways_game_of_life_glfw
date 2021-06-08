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

}

void cursorEnterCallback(GLFWwindow* window, int entered) {
	if (entered) {
		std::cout << "entered window \n";
	}
	else {
		std::cout << "left window \n";
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << "Left button pressed\n";
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		std::cout << "Left button released\n";
	}
}