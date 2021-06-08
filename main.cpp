// conway_game_of_life.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <random>
#include <chrono>
#include <thread>
#include "game_logic.h"
#include "input.h"

int main()
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    const int genDelay = 50; // time to sleep (in ms) after each generation is drawn and updated

    const int cols = 32;
    const int rows = 32;
    const int scale = 20;
    const int cellX = scale;
    const int cellY = scale;

    const int screenW = cols * scale;
    const int screenH = rows * scale;

    double mouseX;
    double mouseY;

    bool paused = false;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenW, screenH, "Hello World", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    srand(time(NULL)); 
    std::vector<std::vector<bool>> oldArr(cols, std::vector<bool>(rows, 0));
    std::vector<std::vector<bool>> nextArr(cols, std::vector<bool>(rows, 0));
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            oldArr[i][j] = rand() % 2; // fill grid with random 0 or 1
        }
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    /* set viewport so that coordinates are now relative to screenW and screenH (0 to screenW) 
     rather than relative to center point (-1 to 1)*/
    glViewport(0.0f, 0.0f, screenW, screenH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenW, 0, screenH, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);
        /* Render here */

        glColor3f(0.1, 1.0, 0.1);


        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { // check if space was pressed
            paused = !paused;
            if (paused) {
                std::cout << "Paused\n";
            }
            else {
                std::cout << "Unpaused\n";
            }
        }
        
        if(!paused){
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if (oldArr[i][j] == 1) {
                        //draw rectangle if array contains 1 at current indices
                        glRecti(i * cellX, j * cellY, ((i + 1) * cellX) - 2, ((j + 1) * cellY) - 2);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(genDelay));

            update(oldArr, nextArr); // update nextArr using oldArr
            oldArr = nextArr; // make oldArr the same as our updated nextArr

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }
        else {//when paused:
            glfwGetCursorPos(window, &mouseX, &mouseY);
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if (oldArr[i][j] == 1) {
                        //draw rectangle if array contains 1 at current indices
                        glRecti(i * cellX, j * cellY, ((i + 1) * cellX) - 2, ((j + 1) * cellY) - 2);
                    }
                }
            }
            if (mouseX > 0 && mouseX < screenW && mouseY > 0 && mouseY < screenW) {
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) { // check if left mouse was pressed
                    oldArr[mouseX / cellX][rows-1 - ((int)(mouseY / cellY))] = !oldArr[mouseX / cellX][rows-1 - ((int)(mouseY / cellY))];
                    std::cout << "swapping cell state at " << (int)mouseX/cellX << "," << (int)mouseY/cellY << "\n";
                }
            }
            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            std::this_thread::sleep_for(std::chrono::milliseconds(genDelay)); 
        }   

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}