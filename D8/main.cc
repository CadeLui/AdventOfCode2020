#include "../Base/AOC_lib.h"
#include <string>

std::pair<std::string, int> parse(std::string instruction)
{
  std::pair<std::string, int> parsedInstruction;
  std::vector<std::string> splitStruction = splitString(instruction);
  int num = 0;
  if (splitStruction[1][0] == '+') num = std::stoi(splitStruction[1].substr(1));
  else num = -std::stoi(splitStruction[1].substr(1));
  parsedInstruction = std::pair<std::string, int>(splitStruction[0], num);
  return parsedInstruction;
}

int findLooper(std::vector<std::string> instructions)
{
  std::vector<int> passedLines;
  for (int i = 0; i < instructions.size(); i++)
  {
    if (findLocation<int>(passedLines, i) != -1) return passedLines[passedLines.size()-1];
    passedLines.push_back(i);
    std::pair<std::string, int> parsedInstruction = parse(instructions[i]);
    if (parsedInstruction.first == "jmp") i += parsedInstruction.second - 1;
  }
  return -1;
}

int executeUntilLoop(std::vector<std::string> instructions)
{
  int loop = findLooper(instructions);
  int accumulator = 0;
  for (int i = 0; i < instructions.size(); i++)
  {
    if (i == loop) return accumulator;
    std::pair<std::string, int> parsedInstruction = parse(instructions[i]);
    if (parsedInstruction.first == "jmp") i += parsedInstruction.second - 1;
    if (parsedInstruction.first == "acc") accumulator += parsedInstruction.second;
  }
  return accumulator;
}

int main(int argc, char* argv[])
{
  if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
  std::vector<std::string> instructions = sgetData(argv[1]);
  std::cout << findLooper(instructions) << "\n";
  std::cout << executeUntilLoop(instructions) << "\n";
  return 0;
}