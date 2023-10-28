#include "../Base/AOC_lib.h"
#include <ios>
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

std::vector<std::pair<std::string, int>> parseFullInstructions(std::vector<std::string> instructions)
{
  std::vector<std::pair<std::string, int>> parsedInstructions;
  for (std::string instruction : instructions) parsedInstructions.push_back(parse(instruction));
  return parsedInstructions;
}

std::string convertParsedInstructionsToString(std::vector<std::pair<std::string, int>> parsedInstructions)
{
  std::string output;
  for (std::pair<std::string, int> instruction : parsedInstructions)
    output += instruction.first + std::to_string(instruction.second) + "\n";
  return output;
}

int findLooper(std::vector<std::pair<std::string, int>> instructions)
{
  std::vector<int> passedLines;
  for (int i = 0; i < instructions.size(); i++)
  {
    if (findLocation<int>(passedLines, i) != -1) return passedLines[passedLines.size()-1];
    passedLines.push_back(i);
    if (instructions[i].first == "jmp") i += instructions[i].second - 1;
  }
  return -1;
}

int executeUntilLoop(std::vector<std::pair<std::string, int>> instructions)
{
  int loop = findLooper(instructions);
  int accumulator = 0;
  for (int i = 0; i < instructions.size(); i++)
  {
    if (i == loop) return accumulator;
    if (instructions[i].first == "jmp") { i += instructions[i].second - 1; continue; }
    if (instructions[i].first == "acc") accumulator += instructions[i].second;
  }
  return accumulator;
}

std::vector<std::pair<std::string, int>> fixLoop(std::vector<std::pair<std::string, int>> oldInstructions)
{
  std::vector<std::pair<std::string, int>> instructions = oldInstructions;
  int loopLocation = findLooper(instructions);
  int cycles = 0;
  while (loopLocation != -1)
  {
    std::cout << "Cycle " << ++cycles << "..\n";
    for (int i = instructions.size()-1; i >= 0; i--)
    {
      instructions = oldInstructions;
      if (instructions[i].first == "nop") instructions[i].first = "jmp";
      else if (instructions[i].first == "jmp") instructions[i].first = "nop";
      loopLocation = findLooper(instructions);
      if (loopLocation == -1) break; 
    }
  }
  return instructions;
}

int main(int argc, char* argv[])
{
  if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
  std::vector<std::string> instructions = sgetData(argv[1]);
  std::vector<std::pair<std::string, int>> parsedInstructions = parseFullInstructions(instructions);
  std::cout << executeUntilLoop(parsedInstructions) << "\n";
  std::vector<std::pair<std::string, int>> fixedInstructions = fixLoop(parsedInstructions);
  std::cout << executeUntilLoop(fixedInstructions);
  return 0;
}
