#include <iostream>
#include <string>
#include <vector>
#include <array>

class Grid {
public:
    // CONSTRUCTOR
    Grid(std::vector<std::string> g);
    // ACCESSORS
    int getX();
    char getValue(int x, int y);

private:
    int x;
    char grid[][x];
};