#include "../Base/AOC_lib.h"
#include <memory>

struct Bag 
{
    std::string description;
    std::vector<std::pair<int, std::shared_ptr<Bag>>> listOfContents;
    Bag(std::string desc)
    {
        this->description = desc;
    }
};

std::shared_ptr<Bag> findBagFromString(std::vector<std::shared_ptr<Bag>> bags, std::string bagDescription)
{
    for (std::shared_ptr<Bag> bag : bags) if (bag->description == bagDescription) return bag;
    return std::make_shared<Bag>("null");
}

std::shared_ptr<Bag> getBagFromLine(std::string line)
{
    std::vector<std::string> splitLine = splitString(line);
    std::shared_ptr<Bag> bag = std::make_shared<Bag>(splitLine[0] + splitLine[1]);
    return bag;
}

void giveBagsTheirChildren(std::vector<std::shared_ptr<Bag>> bags, std::vector<std::string> lines)
{
    for (std::string line : lines)
    {
        line = replaceChars(line, ",", "");
        std::vector<std::string> splitLine = splitString(line);
        std::shared_ptr<Bag> referenceBag = findBagFromString(bags, splitLine[0] + splitLine[1]);
        if (splitLine[4] == "no") continue;
        for (int i = 4; i < splitLine.size(); i += 4)
        {
            referenceBag->listOfContents.push_back
            (
                std::pair<int, std::shared_ptr<Bag>>
                (
                    std::stoi(splitLine[i]), 
                    findBagFromString(bags, splitLine[i+1] + splitLine[i+2])
                )
            );
        }
    }
}

int digThroughContainer(std::shared_ptr<Bag> bag, std::string containedBag)
{
    int count = 0;
    for (std::pair<int, std::shared_ptr<Bag>> contentDesc : bag->listOfContents)
    {
        if (contentDesc.second->description == containedBag) return 1;
        else count += digThroughContainer(contentDesc.second, containedBag);
        if (count > 0) return 1;
    }
    return 0;
}

int findValidContainers(std::vector<std::shared_ptr<Bag>> bags, std::string containedBag)
{
    int containers = 0;
    for (std::shared_ptr<Bag> bag : bags)
        containers += digThroughContainer(bag, containedBag);
    return containers;
}

int findHowManyBagsInOneBag(std::shared_ptr<Bag> bag)
{
    int numOfBags = 0;
    for (std::pair<int, std::shared_ptr<Bag>> content : bag->listOfContents)
        numOfBags += content.first * findHowManyBagsInOneBag(content.second) + content.first;
    return numOfBags;
}

int main(int argc, char* argv[])
{
    if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
    std::vector<std::string> lines = sgetData(argv[1]);
    std::vector<std::shared_ptr<Bag>> bags;
    for (std::string line : lines)
        bags.push_back(getBagFromLine(line));
    giveBagsTheirChildren(bags, lines);
    std::cout << findValidContainers(bags, "shinygold") << "\n";
    std::cout << findHowManyBagsInOneBag(findBagFromString(bags, "shinygold")) << "\n";
}
