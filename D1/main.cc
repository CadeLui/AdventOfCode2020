#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> sgetData(std::string filename)
{
    std::vector<std::string> data;
    std::ifstream fdata;
    fdata.open(filename);
    std::string line;
    while (getline(fdata, line))
        data.push_back(line);
    return data;
}

std::vector<int> igetData(std::string filename)
{
    std::vector<int> data;
    std::ifstream fdata;
    fdata.open(filename);
    std::string line;
    while (getline(fdata, line))
        data.push_back(std::stoi(line));
    return data;
}

int findProducts(std::vector<int> data)
{
    for (int reference = 0; reference < data.size(); reference++)
    {
        for (int i = reference; i < data.size(); i++)
        {
            if (data[reference] + data[i] == 2020)
            {
                return data[reference] * data[i];
            }
        }
    }
    return 0;
}

int findThreeProducts(std::vector<int> data)
{
    for (int r1 = 0; r1 < data.size(); r1++)
    {
        for (int r2 = r1+1; r2 < data.size(); r2++)
        {
            for (int i = r2+1; i < data.size(); i++)
            if (data[r1] + data[r2] + data[i] == 2020)
            {
                return data[r1] * data[i] * data[r2];
            }
        }
    }
    return 0;
}

int main(void)
{
    std::vector<int> data = igetData("example.txt");
    std::cout << findThreeProducts(data) << "\n";
    std::cout << findProducts(data) << "\n";
}