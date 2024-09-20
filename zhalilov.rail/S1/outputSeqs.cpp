#include "outputSeqs.hpp"

#include <iostream>
#include <stdexcept>
#include <limits>

#include "outputList.hpp"

size_t zhalilov::countSum(const List< size_t > &list)
{
  size_t max = std::numeric_limits< size_t >::max();
  size_t sum = 0;
  List< size_t >::const_iterator it = list.cbegin();
  while (it != list.cend())
  {
    if (sum > max - *it)
    {
      throw std::overflow_error("total sum is too large");
    }
    sum += *it;
    it++;
  }
  return sum;
}

std::ostream &zhalilov::outputSeqs(List< strListPair > sequences, std::ostream &output)
{
  auto currIt = sequences.begin();
  auto lastIt = sequences.end();
  size_t longestList = 0;
  List< std::string > names;
  while (currIt != lastIt)
  {
    longestList = std::max(longestList, currIt->second.capacity());
    names.push_back(currIt->first);
    currIt++;
  }
  outputList(output, names);
  output << '\n';

  if (longestList == 0)
  {
    output << "0";
    return output;
  }

  List< List< size_t > > listOfNumbersList;
  for (size_t i = 0; i < longestList; i++)
  {
    listOfNumbersList.push_back(List< size_t >());
    currIt = sequences.begin();
    while (currIt != lastIt)
    {
      List< size_t > &oldNumList = currIt->second;
      if (!oldNumList.empty())
      {
        List< size_t > &lastSeq = listOfNumbersList.back();
        lastSeq.push_back(oldNumList.front());
        oldNumList.pop_front();
      }
      currIt++;
    }
  }

  auto listOfListsIt = listOfNumbersList.cbegin();
  auto listOfListsEnd = listOfNumbersList.cend();
  while (listOfListsIt != listOfListsEnd)
  {
    outputList(output, *listOfListsIt);
    output << '\n';
    listOfListsIt++;
  }

  List< size_t > sums;
  while (!listOfNumbersList.empty())
  {
    List< size_t > &currNumList = listOfNumbersList.front();
    sums.push_back(countSum(currNumList));
    listOfNumbersList.pop_front();
  }
  outputList(output, sums);
  return output;
}
