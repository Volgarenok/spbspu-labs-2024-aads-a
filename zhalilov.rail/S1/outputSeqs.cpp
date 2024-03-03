#include "outputSeqs.hpp"

#include <iostream>

std::ostream &zhalilov::outputSeqs(List< pair > sequences, std::ostream &output)
{
  List< pair >::iterator currIt = sequences.begin();
  List< pair >::iterator lastIt = sequences.end();
  std::string txtToOutput = "";
  while (currIt != lastIt)
  {
    txtToOutput += currIt->first + " ";
    currIt++;
  }

  bool allEmpty = false;
  while (!allEmpty)
  {
    txtToOutput += "\n";
    currIt = sequences.begin();
    allEmpty = true;
    while (currIt != lastIt)
    {
      List< size_t > &currList = currIt->second;
      if (!currList.empty())
      {
        allEmpty = false;
        txtToOutput += currList.front() + " ";
        currList.pop_front();
      }
      currIt++;
    }
  }
  output << txtToOutput;
  return output;
}
