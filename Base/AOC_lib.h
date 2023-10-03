#pragma once

/**
 * @file AOC_lib.h
 * @author Cade Luinenburg (clui83@outlook.com)
 * @brief A collection of includes and shared functions for Advent of Code
 * @version 0.2
 * @date 2023-08-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string getData(char* filename)
{
    std::string data;
    std::ifstream fdata(filename);
    while (fdata)
        data += fdata.get();
    return data;
}

std::vector<std::string> sgetData(char* filename)
{
    std::vector<std::string> data;
    std::ifstream fdata;
    fdata.open(filename);
    std::string line;
    while (getline(fdata, line))
        data.push_back(line);
    fdata.close();
    return data;
}

std::vector<int> igetData(char* filename)
{
    std::vector<int> data;
    std::ifstream fdata;
    fdata.open(filename);
    std::string line;
    while (getline(fdata, line))
        data.push_back(std::stoi(line));
    fdata.close();
    return data;
}

std::vector<std::vector<char>> cvgetData(char* filename)
{
    std::vector<std::vector<char>> data;
    std::ifstream fdata;
    fdata.open(filename);
    std::string line;
    while (getline(fdata, line))
    {
        std::vector<char> newRow;
        for (char col : line)
            newRow.push_back(col);
        data.push_back(newRow);
    }
    fdata.close();
    return data;
}

std::vector<std::string> splitString(std::string unsplit, std::string delim=" ")
{
    std::vector<std::string> split;
    std::string segment = "";
    for (int i = 0; i < unsplit.length(); i++)
    {
        if (unsplit[i] == delim[0])
        {
            std::string temp_segment = "";
            for (int i2 = 0; i2 < delim.length(); i2++)
                temp_segment += unsplit[i+i2];
            if (temp_segment == delim)
            {
                split.push_back(segment);
                segment = "";
                i += delim.length();
            }
        }
        segment += unsplit[i];
    }
    split.push_back(segment.substr(0, segment.length()-1));
    return split;
}

std::string removeNewLines(std::string line)
{
    std::string cleanLine;
    for (char letter : line)
    {    
        if (letter != '\n')
            cleanLine += letter;
        else
            cleanLine += " ";
    }
    return cleanLine;
}