#include "../Base/AOC_lib.h"
#include <memory>

struct BagContents 
{
    int numOfContents;
    std::string descriptionOfContents;
    BagContents(int num, std::string contents)
    {
        this->numOfContents = num;
        this->descriptionOfContents = contents;
    }
};

struct Bag 
{
    std::string description;
    std::vector<std::shared_ptr<BagContents>> listOfContents;
    Bag(std::string desc)
    {
        this->description = desc;
    }
};

std::shared_ptr<Bag> getBagFromLine(std::string line)
{
    std::vector<std::string> splitLine = splitString(line);
    std::shared_ptr<Bag> bag = std::make_shared<Bag>(splitLine[0] + splitLine[1]);
    for (int i = 4; i < splitLine.size(); i+=4)
    {
        if (splitLine[i] == "no") continue;
        bag->listOfContents.push_back(std::make_shared<BagContents>(std::stoi(splitLine[i]), splitLine[i+1] + splitLine[i+2]));
    }
    return bag;
}

int main(int argc, char* argv[])
{
    if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
    std::vector<std::string> data = sgetData(argv[1]);
    std::vector<std::shared_ptr<Bag>> bags;
    for (std::string line : data)
        bags.push_back(getBagFromLine(line));
    std::vector<std::string> goldHolders;
    int numGoldHolders = -1;
    while (numGoldHolders != goldHolders.size())
    {
        numGoldHolders = goldHolders.size();
        for (std::shared_ptr<Bag> bag : bags)
        {
            if (findAndReturnTrue(goldHolders, bag->description)) continue;
            for (std::shared_ptr<BagContents> contents : bag->listOfContents)
            {
                if (contents->descriptionOfContents == "shinygold") {goldHolders.push_back(bag->description); break; }
                if (findAndReturnTrue(goldHolders, contents->descriptionOfContents)) {goldHolders.push_back(bag->description); break; }
            }
        }
    }
    for (std::string bag : goldHolders) std::cout << bag << "\n";
    std::cout << goldHolders.size() << ":" << numGoldHolders << "\n";
}
