#include "inputOutput.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <iterator>
#include <stdexcept>
#include <list.hpp>

void sivkov::outputNames(List< std::pair< std::string, List< size_t > > >& list, std::ostream& out)
{
  if (list.empty())
  {
    throw std::logic_error("list is empty");
  }
  list.reverse();
  for (auto it = list.cbegin(); it != list.cend(); ++it)
  {
    if (it != list.cbegin())
    {
      out << ' ';
    }
    out << it->first;
  }
  out << "\n";
}

void sivkov::outputSums(const List< size_t >& numbers, std::ostream& out)
{
  for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
  {
    if (it != numbers.cbegin())
    {
      out << ' ';
    }
    out << *it;
  }
}

void sivkov::input(std::istream& input, List< std::pair< std::string, List< size_t > > >& list)
{
  while (!input.eof())
  {
    input.clear();
    std::pair< std::string, List< size_t > > temp;
    input >> temp.first;
    if (temp.first.empty())
    {
      break;
    }
    size_t number = 0;
    while (input >> number)
    {
      temp.second.push_front(number);
    }
    list.push_front(temp);
  }
}

void sivkov::outputNums(const List< std::pair< std::string, List< size_t > > >& list, List< size_t >& numbers, std::ostream& out)
{
  bool overflowFlag = false;
  bool allData = true;
  size_t maxNums = 0;
  size_t sum = 0;
  size_t size = 0;

  for (auto iteratorForPair = list.cbegin(); iteratorForPair != list.cend(); ++iteratorForPair)
  {
    size_t sizeOfList = iteratorForPair->second.getSize();
    if (sizeOfList > maxNums)
    {
      maxNums = sizeOfList;
    }
  }

  for (size_t i = 0; i < maxNums; ++i)
  {
    sum = 0;
    allData = false;

    for (auto iteratorForPair = list.cbegin(); iteratorForPair != list.cend(); ++iteratorForPair)
    {
      auto iteratorForNums = iteratorForPair->second.cbegin();
      for (size_t j = 0; j < i; ++j)
      {
        if (iteratorForNums != iteratorForPair->second.cend())
        {
          ++iteratorForNums;
        }
      }

      if (iteratorForNums != iteratorForPair->second.cend())
      {
        if (allData)
        {
          out << " ";
        }
        if (std::numeric_limits< size_t >::max() - sum >= *iteratorForNums)
        {
          sum += *iteratorForNums;
        }
        else
        {
          overflowFlag = true;
        }
        out << *iteratorForNums;
        allData = true;
      }
      ++size;
    }
    if (allData)
    {
      out << "\n";
      numbers.push_front(sum);
    }
  }
  if (allData && size == 0)
  {
    numbers.push_front(sum);
  }
  numbers.reverse();
  if (overflowFlag == true)
  {
    throw (std::overflow_error("overflow"));
  }
}
