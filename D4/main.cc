#include "../Base/AOC_lib.h"

bool testValid(std::vector<std::string> fields)
{
    std::string valids[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    int correctFields = 0; 
    for (std::string field : fields)
    {
        for (std::string test_field : valids)
            if (field.substr(0, 3) == test_field)
            {
                correctFields++;
                break;
            }
    }
    return correctFields == 7;

}

int main(int argc, char* argv[])
{
    
    std::string data = getData(argv[1]);
    std::vector<std::string> split_data = splitString(data, "\n\n");
    int realPasses = 0;
    for (std::string section : split_data)
    {
        if (testValid(splitString(removeNewLines(section)))) realPasses++;
    }
    std::cout << realPasses << "\n";
    return 0;
}