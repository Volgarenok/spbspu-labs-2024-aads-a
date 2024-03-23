#include "inputOutputList.hpp"
#include <iostream>
#include "list.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

void chistyakov::inputList(std::istream & input, List< std::pair< std::string, List < int > > > & list)
{
  std::string name = "";
  std::string line = "";
  input >> line;

  while (!input.eof())
  {
    name = line;
    List< int > nums;
    while (input >> line && std::isdigit(line[0]))
    {
      std::size_t num = std::stoull(line);
      nums.push_back(num);
    }
    list.push_back({name, nums});
  }
}

int chistyakov::maxDigit(List< std::pair< std::string, List < int > > > & list)
{
  int max_digit = 1;

  for (auto element = list.begin(); element != list.end(); ++element)
  {
    int index = 0;

    for (auto numList = element->second.begin(); numList != element->second.end(); ++numList)
    {
      index++;
      std::max(max_digit, index);
    }
  }

  return max_digit;
}

void chistyakov::outPutNames(List < std::pair < std::string, List < int > > > & list)
{
  for (auto element = list.begin(); element != list.end(); ++element)
  {
    std::cout << element->first;
    auto next = element;
    if (++next != list.end())
    {
      std::cout << " ";
    }
  }
}

void chistyakov::outPutNums(List < std::pair < int, List < int > > > & list)
{
  for (auto element = list.begin(); element != list.end(); ++element)
  {
    for (auto num = (element->second).begin(); num != (element->second).end(); ++num)
    {
      std::cout << *num;
      auto next = num;

      if (next.get_BiList()->next_ != nullptr)
      {
        std::cout << " ";
      }
    }

    std::cout << "\n";
  }
}

void chistyakov::outPutSums(List < std::pair < int, List < int > > > & list)
{
  for (auto element = list.begin(); element != list.end(); ++element)
  {
    std::cout << element->first;
    auto next = element;
    if (++next != list.end())
    {
      std::cout << " ";
    }
  }
}

