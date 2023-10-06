#include "../Base/AOC_lib.h"

int getRow(std::string instructions, int low=0, int upp=127, int index=0)
{
    if (index > 6)
    {
        if (instructions[index-1] == 'B') return upp;
        else return low;
    }
    int half = (upp-low)/2+1;
    char action = instructions[index];
    if (action == 'B')
        return getRow(instructions, low+half, upp, index+1);
    if (action == 'F')
        return getRow(instructions, low, upp-half, index+1);
    return -1;
}

int getCol(std::string instructions, int low=0, int upp=7, int index=7)
{
    if (index > instructions.length()-1)
    {
        if (instructions[index-1] == 'R') return upp;
        else return low;
    }
    int half = (upp-low)/2+1;
    char action = instructions[index];
    if (action == 'R')
        return getCol(instructions, low+half, upp, index+1);
    if (action == 'L')
        return getCol(instructions, low, upp-half, index+1);
    return -1;
}

int getID(int row, int col)
{
    return row*8 + col;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> data = sgetData(argv[1]);
    std::vector<int> ids;
    for (std::string line : data)
    {
        int row = getRow(removeNewLines(line));
        int col = getCol(removeNewLines(line));
        ids.push_back(getID(row, col));
    }
    std::cout << vectorMax(ids) << "\n";
    std::sort(ids.begin(), ids.end());
    for (int i = 0; i < ids.size()-2; i++)
    {
        if (ids[i+1] - ids[i] != 1) std::cout << ids[i]+1 << "\n";
    }
    return 0;
}