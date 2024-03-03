#include "outputSeqs.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

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

  size_t max = std::numeric_limits< size_t >::max();
  size_t sum = 0;

  bool allEmpty = false;
  while (!allEmpty)
  {
    sum = 0;
    txtToOutput += "\n";
    currIt = sequences.begin();
    allEmpty = true;
    while (currIt != lastIt)
    {
      List< size_t > &currList = currIt->second;
      if (!currList.empty())
      {
        allEmpty = false;
        size_t number = currList.front();

        if (sum > max - number)
        {
          throw std::overflow_error("total summary is too large");
        }

        sum += number;
        txtToOutput += number + " ";
        currList.pop_front();
      }
      currIt++;
    }
  }
  output << txtToOutput;
  return output;
}
