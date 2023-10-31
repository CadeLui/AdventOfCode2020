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

bool numTester(int num, int min, int max)
{ return (num < min || num > max); }

bool testFieldValidity(std::vector<std::string> fields)
{
    std::cout << "set\n";
    for (std::string full_field : fields)
    {
        std::string field = full_field.substr(0, 3);
        std::string data = removeNewLines(full_field.substr(4));
        if ((int) data[data.length()-1] == -1) data = data.substr(0, data.length()-1);
        if (field == "byr")
            if (numTester(atoi(data.c_str()), 1920, 2020)) return false;
        if (field == "iyr")
            if (numTester(atoi(data.c_str()), 2010, 2020)) return false;
        if (field == "eyr")
            if (numTester(atoi(data.c_str()), 2020, 2030)) return false;
        if (field == "hgt")
        {
            std::string suffix = full_field.substr(full_field.length()-2);
            if (suffix.compare("in") != 0 && suffix.compare("cm") != 0) return false;
            int num = atoi(full_field.substr(4, full_field.length()-2).c_str());
            if (suffix.compare("cm") == 0 && numTester(num, 150, 193)) return false;
            if (suffix.compare("in") == 0 && numTester(num, 59, 76)) return false;
        }
        if (field == "hcl") // haha hydrochloric acid
        {
            if (data[0] != '#') return false;
            std::string valids = "1234567890abcdef";
            data = data.substr(1);
            int nvalids = 0;
            for (char symbol : data) for (char valid_symbol : valids) if (valid_symbol == symbol) {nvalids++; break;}
            if (nvalids < 6) return false;
        }
        if (field == "ecl")
        {
            std::string valids[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            bool safe = false;
            for (std::string valid : valids) if (valid == data) {safe = true; break; }
            if (!safe) return false;
        }
        if (field == "pid")
        {
            try {atoi(data.c_str());}
            catch(const std::exception& e) {return false;}
            if (data.length() != 9) return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    
    std::string data = getData(argv[1]);
    std::vector<std::string> split_data = splitString(data, "\n\n");
    int realPasses = 0;
    for (std::string section : split_data)
    {
        if (testValid(splitString(removeNewLines(section))) && testFieldValidity(splitString(removeNewLines(section)))) realPasses++;
    }
    std::cout << realPasses << "\n";
    return 0;
}