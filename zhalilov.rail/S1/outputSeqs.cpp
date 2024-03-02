#include "outputSeqs.hpp"

#include <iostream>

std::ostream &zhalilov::outputSeqs(List< pair > sequences, std::ostream &output)
{
  List< pair >::iterator currIt = sequences.begin();
  List< pair >::iterator lastIt = sequences.end();
  while (currIt != lastIt)
  {
    output << currIt->first << " ";
    currIt++;
  }
  output << "\n";

  bool allEmpty = false;
  while (!allEmpty)
  {
    currIt = sequences.begin();
    allEmpty = true;
    while (currIt != lastIt)
    {
      List< size_t > &currList = currIt->second;
      if (!currList.empty())
      {
        allEmpty = false;
        output << currList.front() << " ";
        currList.pop_front();
      }
      currIt++;
    }
    output << "\n";
  }
  return output;
}
