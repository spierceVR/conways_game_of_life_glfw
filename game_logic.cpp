// game logic functions
#include "game_logic.h"

int countNeighbors(std::vector<std::vector<int>>& grid, int& x, int& y) {
    int sum = 0;
    const int cols = grid.size();
    const int rows = grid[0].size();

    // count alive neighboring cells
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            
            int col = (x + i + cols) % cols;
            int row = (y + j + rows) % rows;

            sum += grid[row][col];
        }
    }
    // remove self from count
    sum -= grid[y][x];

    return sum;
}

std::vector<std::vector<int>> update(std::vector<std::vector<int>>& old, std::vector<std::vector<int>>& next) {
    const int cols = old.size();
    const int rows = old[0].size();

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            const int alive = countNeighbors(old, i, j);
            switch (alive) {
            case 2:
                break;
            case 3:
                next[j][i] = 1;
                break;
            default:
                next[j][i] = 0;
                break;
            }

        }
    }
    return next;
}