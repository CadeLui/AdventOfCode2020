#include "../Base/AOC_lib.h"

bool getTree(std::vector<std::string> map, int row, int col)
{
    while (row >= map.size()) row -= map.size();
    while (col >= map[0].size()) col -= map[0].size();
    return map[row][col] == '#';
}

int getTreesAlongSlope(int rowShift, int colShift, std::vector<std::string> map)
{
    int trees = 0;
    for (int iterator = 0; iterator*rowShift < map.size(); iterator ++)
        if (getTree(map, iterator*rowShift, iterator*colShift)) trees ++;
    return trees;
}

std::vector<int> getTreesAlongManySlopes(std::vector<std::vector<int>> slopes, std::vector<std::string> map)
{
    std::vector<int> trees;
    for (std::vector<int> slope : slopes)
        trees.push_back(getTreesAlongSlope(slope[0], slope[1], map));
    return trees;
}

int main(int argc, char* argv[])
{
    if (argc < 2) return -1;
    std::vector<std::string> lines = sgetData(argv[1]);
    std::cout << getTreesAlongSlope(1, 3, lines) << "\n";
    std::vector<std::vector<int>> slopes = {{1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}};
    std::vector<int> trees = getTreesAlongManySlopes(slopes, lines);
    int product = 1;
    for (int i : trees) product *= i;
    std::cout << product << "\n";
}