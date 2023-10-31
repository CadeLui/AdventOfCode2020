#include "../Base/AOC_lib.h"

std::vector<int> getRange(std::string line)
{
    int dash_pos = line.find("-");
    int space_pos = line.find(" ");
    std::string sec_one = line.substr(0, dash_pos);
    std::string sec_two = line.substr(dash_pos+1, space_pos-dash_pos);
    std::vector<int> vals;
    vals.push_back(std::stoi(sec_one));
    vals.push_back(std::stoi(sec_two));
    return vals;
}

std::string getPass(std::string line)
{return line.substr(line.find(" ") + 4);}

std::string getKey(std::string line)
{return line.substr(line.find(" ")+1, 1);}

bool testValid(std::vector<int> range, std::string key, std::string pass)
{
    int count = 0;
    for (char character : pass)
    {
        if (character == key[0]) count += 1;
        if (count > range[1]) return false;
    }
    if (count < range[0]) return false;
    return true;
}

std::vector<std::string> findValids(std::vector<std::string> lines)
{
    std::vector<std::string> valids;
    for (std::string line: lines)
    {
        std::vector<int> range = getRange(line);
        std::string key = getKey(line);
        std::string pass = getPass(line);
        if (testValid(range, key, pass)) valids.push_back(line);
    }
    return valids; 
}

bool testNewValid(std::vector<int> indexes, std::string key, std::string pass)
{
    return (pass[indexes[0]-1] != pass[indexes[1]-1]) && (pass[indexes[0]-1] == key[0] || pass[indexes[1]-1] == key[0]);
}

std::vector<std::string> findNewValids(std::vector<std::string> lines)
{
    std::vector<std::string> valids;
    for (std::string line: lines)
    {
        std::vector<int> indexes = getRange(line);
        std::string key = getKey(line);
        std::string pass = getPass(line);
        if (testNewValid(indexes, key, pass)) valids.push_back(line);
    }
    return valids; 
}

int main(int argc, char* argv[])
{
    if (argc < 2) return -1;
    std::vector<std::string> lines = sgetData(argv[1]);
    std::cout << findNewValids(lines).size() << "\n";
}