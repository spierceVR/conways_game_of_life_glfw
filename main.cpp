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

    const int cols = 32;
    const int rows = 32;
    const int scale = 20;
    const int cellx = scale;
    const int celly = scale;

    const int screenW = cols * scale;
    const int screenH = rows * scale;

    bool paused = false;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenW, screenH, "Hello World", NULL, NULL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    srand(time(NULL)); 
    std::vector<std::vector<int>> oldArr(cols, std::vector<int>(rows, 0));
    std::vector<std::vector<int>> nextArr(cols, std::vector<int>(rows, 0));
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            oldArr[i][j] = rand() % 2;;
        }
    }
    nextArr = oldArr;

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

        glColor3f(1.0, 1.0, 1.0);


        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { // check if space was pressed and released
            paused = !paused;
        }
        
        if(!paused){
            for (int i = 0; i < cols; i++) {
                for (int j = 0; j < rows; j++) {
                    if (nextArr[i][j] == 1) {
                        //draw rectangle if array contains 1 at current indices
                        glRecti(i * cellx, j * celly, ((i + 1) * cellx) - 2, ((j + 1) * celly) - 2);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            nextArr = update(oldArr, nextArr); // update nextArr using oldArr
            oldArr = nextArr; // make oldArr the same as our updated nextArr

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(120)); // add 20 second guess for draw time to normal 330ms delay 
        }   

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}