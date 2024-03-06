#include "inputOutput.hpp"
#include <iostream>
#include <string>
#include "list.hpp"
#include "exception"

void outputNames(List<std::pair<std::string, List<size_t>>>& list)
{
  if (list.empty())
  {
    throw std::invalid_argument("");
  }
  for (auto it = list.cbegin(); it != list.cend(); ++it)
  {
    std::cout << it->first;
    auto temp = it;
    ++temp;
    if (temp != list.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

void outputSums(List<size_t> &numbers)
{
  for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
  {
    std::cout << *it;
    auto temp = it;
    ++temp;
    if (temp != numbers.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

void input(std::istream& input, List<std::pair<std::string, List<size_t>>>& list)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    list.push_front({ line, List<size_t>{} });
    while (input >> line)
    {
      try
      {
        size_t number = std::stoull(line);
        list.front().second.push_back(number);
      }
      catch (const std::invalid_argument&)
      {
        break;
      }
    }
  }
}

void addnum(List<std::pair<std::string, List<size_t>>>& list, List<size_t>& numbers)
{
  bool allData = true;
  size_t maxNums = 0;
  size_t sum = 0;

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
      iteratorForNums.advance(i);

      if (iteratorForNums != iteratorForPair->second.cend())
      {
        if (allData)
        {
          std::cout << " ";
        }
        if (std::numeric_limits<size_t>::max() - sum >= *iteratorForNums)
        {
          sum += *iteratorForNums;
        }
        else
        {
          throw std::out_of_range("OverFlow");
          continue;
        }
        std::cout << *iteratorForNums;
        allData = true;
      }
    }
    if (allData)
    {
      std::cout << "\n";
      numbers.push_front(sum);
    }
  }
}
