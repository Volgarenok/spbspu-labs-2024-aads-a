#include "inputOutputList.hpp"
#include <iostream>
#include "list.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

void chistyakov::inputList(std::istream & input, List< std::pair< std::string, List < size_t > > > & list)
{
  std::string name = "";
  std::string line = "";
  input >> line;

  while (!input.eof())
  {
    name = line;
    List< size_t > nums;
    while (input >> line && std::isdigit(line[0]))
    {
      nums.push_back(std::stoull(line));
    }
    list.push_back(std::pair< std::string, List < size_t > >(name, nums));
  }
}

size_t chistyakov::maxDigit(List< std::pair< std::string, List < size_t > > > & list)
{
  size_t max_digit = 1;

  for (auto element = list.begin(); element != list.end(); ++element)
  {
    size_t index = 0;

    for (auto numList = element->second.begin(); numList != element->second.end(); ++numList)
    {
      index++;
      max_digit = std::max(max_digit, index);
    }
  }

  return max_digit;
}

void chistyakov::outputNames(List < std::pair < std::string, List < size_t > > > & list)
{
  if (!list.empty())
  {
    std::cout << list.begin()->first;
  }

  for (auto element = ++list.begin(); element != list.end(); ++element)
  {
    std::cout << " " << element->first;
  }
}

void chistyakov::outputNums(List < std::pair < size_t, List < size_t > > > & list)
{
  for (auto element = list.begin(); element != list.end(); ++element)
  {
    if (!element->second.empty())
    {
       std::cout << *(element->second).begin();
    }

    for (auto num = ++(element->second).begin(); num != (element->second).end(); ++num)
    {
      std::cout << " " << *num;
    }

    std::cout << "\n";
  }
}

void chistyakov::outputSums(List < std::pair < size_t, List < size_t > > > & list)
{
  if (!list.empty())
  {
    std::cout << list.begin()->first;
  }

  for (auto element = ++list.begin(); element != list.end(); ++element)
  {
    std::cout << " " << element->first;
  }
}
