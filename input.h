#pragma once
#include "include/GLFW/glfw3.h"
#include <iostream>

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods );
void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);