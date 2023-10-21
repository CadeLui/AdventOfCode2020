#include "../Base/AOC_lib.h"
#include <memory>
#include <map>

struct Bag 
{
    std::string description;
    std::map<int, std::shared_ptr<Bag>> listOfContents;
    Bag(std::string desc)
    {
        this->description = desc;
    }
};

std::shared_ptr<Bag> getBagFromLine(std::string line)
{
    std::vector<std::string> splitLine = splitString(line);
    std::shared_ptr<Bag> bag = std::make_shared<Bag>(splitLine[0] + splitLine[1]);
    return bag;
}

int main(int argc, char* argv[])
{
    if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
    std::vector<std::string> data = sgetData(argv[1]);
    std::vector<std::shared_ptr<Bag>> bags;
    for (std::string line : data)
        bags.push_back(getBagFromLine(line));
}
