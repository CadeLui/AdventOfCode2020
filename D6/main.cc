#include "../Base/AOC_lib.h"

void partOne(char* filename)
{
    std::vector<std::string> data = getGroupedData(filename);

    int sum = 0;
    for (std::string line : data)
        sum += removeDuplicates(replaceChars(line, " ", "")).length();
    std::cout << sum << "\n";
}

int numsOfAllYesses(std::vector<std::string> group)
{
    group.shrink_to_fit();
    int allYes = 0;
    std::string reference = vectorLongestString(group);
    for (char answer : reference) 
    {
        int sharedYesses = 0;
        for (std::string answers : group)
            if (answers.find(answer) != std::string::npos) sharedYesses++;
        if (sharedYesses == group.size()) allYes++;
    }
    return allYes;
}

void partTwo(char* filename)
{
    std::vector<std::string> data = getGroupedData(filename);
    int sum = 0;
    for (std::string line : data)
        sum += numsOfAllYesses(splitString(line));
    std::cout << sum << "\n";
}

int main(int argc, char* argv[])
{
    if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
    partOne(argv[1]);
    partTwo(argv[1]);
}