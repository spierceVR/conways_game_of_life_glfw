// game logic functions
#include "game_logic.h"

int countNeighbors(std::vector<std::vector<bool>>& grid, const int& x, const int& y) {
    int sum = 0;
    const int cols = grid.size();
    const int rows = grid[0].size();

    // count alive neighboring cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            int col = (x + i + cols) % cols;
            int row = (y + j + rows) % rows;

            sum += (int)grid[row][col];
        }
    }
    // remove self from count
    sum -= (int)grid[y][x];

    return sum;
}

void update(std::vector<std::vector<bool>>& old, std::vector<std::vector<bool>>& next) {
    const int cols = old.size();
    const int rows = old[0].size();

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int neighbours = countNeighbors(old, i, j);
            switch (old[j][i]) {
            case 1:
                if (neighbours < 2 || neighbours > 3) {
                    next[j][i] = 0;
                }
                else {
                    next[j][i] = old[j][i];
                }
                break;
            case 0:
                if (neighbours == 3) {
                    next[j][i] = 1;
                }
                break;
            }
        }
    }
}