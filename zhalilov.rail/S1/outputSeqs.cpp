#include "outputSeqs.hpp"

#include <iostream>
#include <stdexcept>
#include <limits>

#include "outputList.hpp"

std::ostream &zhalilov::outputSeqs(List< pair > sequences, std::ostream &output)
{
  List< pair >::iterator currIt = sequences.begin();
  List< pair >::iterator lastIt = sequences.end();
  size_t longestList = 0;
  List< std::string > names;
  while (currIt != lastIt)
  {
    longestList = std::max(longestList, currIt->second.capacity());
    names.push_back(currIt->first);
    currIt++;
  }
  output << names;
  output << '\n';

  List< List< size_t > > listOfNumbersList;
  for (size_t i = 0; i < longestList; i++)
  {
    listOfNumbersList.push_back(List< size_t >());
    List< size_t > &lastSeq = listOfNumbersList.back();
    currIt = sequences.begin();
    while (currIt != lastIt)
    {
      List< size_t > &oldNumList = currIt->second;
      if (!oldNumList.empty())
      {
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
    output << *listOfListsIt;
    output << '\n';
    listOfListsIt++;
  }
  return output;
}
