#include "outputSeqs.hpp"

#include <iostream>
#include <stdexcept>
#include <limits>

std::ostream &zhalilov::outputSeqs(List< pair > sequences, std::ostream &output)
{
  List< pair >::iterator currIt = sequences.begin();
  List< pair >::iterator lastIt = sequences.end();
  lastIt--;
  size_t longestList = 0;
  std::string txtToOutput = "";
  while (currIt != lastIt)
  {
    longestList = std::max(longestList, currIt->second.capacity());
    txtToOutput += currIt->first + ' ';
    currIt++;
  }
  txtToOutput += currIt->first;

  List< size_t > sumList;
  size_t max = std::numeric_limits< size_t >::max();
  size_t sum = 0;
  for (size_t i = 0; i < longestList; i++)
  {
    txtToOutput += '\n';
    currIt = sequences.begin();
    while (currIt != lastIt)
    {
      List< size_t > &currList = currIt->second;
      if (!currList.empty())
      {
        size_t number = currList.front();
        if (sum > max - number)
        {
          throw std::overflow_error("total summary is too large");
        }
        txtToOutput += std::to_string(number);
        sum += number;
        currList.pop_front();
        if (currList.begin() != currList.end())
        {
          txtToOutput += ' ';
        }
      }
      currIt++;
    }
    sumList.push_back(sum);
    sum = 0;
  }

  txtToOutput += '\n';
  if (sumList.empty())
  {
    txtToOutput += '0';
  }
  else
  {
    while (!sumList.empty())
    {
      txtToOutput += std::to_string(sumList.front()) + ' ';
      sumList.pop_front();
    }
  }
  output << txtToOutput;
  return output;
}
