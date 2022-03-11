#include <iostream>
#include <string>
#include <vector>
#include "grid.h"

Grid::Grid(std::vector<std::string> g) {
    x = g.size();
    for (int i=0; i<g.size(); i++) {
        for (int j=0; j<g[i].size(); j++) {
            grid[i][j]=g[i][j];
        }
    }
}

char Grid::getValue(int x, int y) {
    return grid[x][y];
}

int Grd::getX() {
    return x;
}