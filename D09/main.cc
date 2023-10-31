#include "../Base/AOC_lib.h"
#include <algorithm>
#include <cstdint>
#include <iterator>


long findOutlierIndex(int preambleLength, std::vector<long> data)
{
  long outlier = 0;
  bool success = false;
  for (int rootIndex = preambleLength; rootIndex < data.size(); rootIndex++)
  {
    success = false;
    for (int referenceIndex = 1; referenceIndex < preambleLength+1; referenceIndex++)
    {
      for (int compareIndex = 1; compareIndex < preambleLength+1; compareIndex++)
      {
        if (referenceIndex == compareIndex) continue;
        if (data[referenceIndex] == data[compareIndex]) continue;
        if (data[rootIndex-referenceIndex] + data[rootIndex-compareIndex] == data[rootIndex]) {success = true; break;}
      }
      if (success) break;
    }
    if (!success) return rootIndex;
  }
  return outlier;
}

std::vector<long> findBadNums(int maxIndex, std::vector<long> data)
{
  long sum;
  std::vector<long> badNums;
  for (int startNum = 0; startNum < maxIndex-1; startNum++)
  {
    for (int endNum = startNum+1; endNum < maxIndex; endNum++)
    {
      sum = 0;
      badNums.clear();
      for (int i = startNum; i < endNum+1; i++) 
      {
        sum += data[i];
        badNums.push_back(data[i]);
      }
      if (sum == data[maxIndex]) return badNums;
    }
  }
  return std::vector<long>();
}

int main(int argc, char* argv[])
{ 
  if (argc < 2) { std::cout << "Please provide a filename as a parameter.\n"; return 0; }
  std::vector<std::string> sdata = sgetData(argv[1]);
  std::vector<long> data;
  for (std::string d : sdata)
  {
    data.push_back(std::stol(d));
  }
  long outlierIndex = findOutlierIndex(std::stoi(argv[2]), data);
  std::cout << data[outlierIndex] << "\n";
  std::vector<long> badSet = findBadNums(outlierIndex, data);
  for (long num : badSet) std::cout << num << "\n";
  std::vector<long>::iterator maxIterator = std::max_element(std::begin(badSet), std::end(badSet));
  int realMaxIterator = std::distance(std::begin(badSet), maxIterator);
  std::vector<long>::iterator minIterator = std::min_element(std::begin(badSet), std::end(badSet));
  int realMinIterator = std::distance(std::begin(badSet), minIterator);
  std::cout << badSet[realMinIterator] + badSet[realMaxIterator] << "\n";
  std::cout << realMinIterator << ":" << realMaxIterator << "\n";
}
