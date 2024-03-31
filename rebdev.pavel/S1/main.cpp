#include <iostream>
#include <utility>
#include <string>
#include <limits>

#include "biList.hpp"
#include "BidirectionalIterator.hpp"
#include "pairsFunction.hpp"

int main()
{
  using list = rebdev::BiList< size_t >;
  using stringAndList = std::pair< std::string, list >;
  using iter = rebdev::BidirectionalIterator< size_t >;

  rebdev::BiList< stringAndList > listOfPairs;

  size_t maxNumber = 0;
  std::string listName;

  while (std::cin >> listName)
  {
    list numList;

    try
    {
      size_t listLength = rebdev::inputNumbersList(std::cin, numList);
      maxNumber = std::max(maxNumber, listLength);
      listOfPairs.push_back(stringAndList(listName, numList));
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what();
      return 1;
    }

    listName.clear();
  }

  rebdev::BidirectionalIterator< stringAndList > beg = listOfPairs.begin();
  while (beg != listOfPairs.end())
  {
    iter readIter = (*beg).second.begin();
    //++readIter;
    std::cout << (*beg).first << ' ';
    while (readIter != (*beg).second.end())
    {
      std::cout << (*readIter) << ' ';
      ++readIter;
    }
    ++beg;
  }
  return 0;
}
