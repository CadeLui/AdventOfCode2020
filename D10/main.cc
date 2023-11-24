#include "../Base/AOC_lib.h"
#include <algorithm>

std::vector<int> addImpliedAdapter(std::vector<int> adapters)
{
  adapters.insert(std::begin(adapters), 0);
  adapters.push_back(adapters[adapters.size()-1]+3);
  return adapters;
}

int getNumOfDifferences(std::vector<int> adapters, int difference)
{
  int differences = 0;
  for (int i = 1; i < adapters.size(); i++)
    if (adapters[i] - adapters[i-1] == difference) differences++;
  return differences;
}

long long getPermutations(std::vector<int> adapters, int start=0)
{
  long long permutations = 0;
  int length;
  for (length = start+1; length < adapters.size(); length++)
  {
    if (adapters[length] - adapters[start] > 3) break;
    else permutations += getPermutations(adapters, length);
  }
  if (length == adapters.size()-1) {return ++permutations;}
  return permutations;
}

int main(int argc, char* argv[])
{ 
  if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
  std::vector<int> data = igetData(argv[1]);
  std::sort(std::begin(data), std::end(data));
  data = addImpliedAdapter(data);
  data.shrink_to_fit();
  std::cout << getNumOfDifferences(data, 1) * getNumOfDifferences(data, 3) << "\n";
  std::cout << getPermutations(data) << "\n";
}
