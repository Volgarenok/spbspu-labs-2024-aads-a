#include <iostream>
#include <limits>

#include "doubly_linked_lis.h"

using pairsOfList = serter::Doubly_linked_list< std::pair< std::string, serter::Doubly_linked_list< size_t > > >;

void inputList(pairsOfList& pairsList, std::istream& input)
{
  while (!input.eof())
  {
    input.clear();
    std::pair< std::string, serter::Doubly_linked_list< size_t > > pair{};
    input >> pair.first;
    if (pair.first.empty())
    {
      return;
    }
    size_t num = {};
    while (input >> num)
    {
      pair.second.push(num);
    }
    pairsList.push(pair);
  }
}

void outputList(pairsOfList& pairsList, std::ostream& output)
{
  if (pairsList.is_empty())
  {
    output << '0';
    return;
  }
  auto names = pairsList.begin();
  bool anotherName = false;
  while (names != pairsList.end())
  {
    if (anotherName)
    {
      output << ' ';
    }
    output << names->first;
    ++names;
    anotherName = true;
  }
  output << '\n';
  size_t max = 0;
  for (auto p : pairsList)
  {
    size_t size = p.second.get_size();
    max = std::max(max, size);
  }
  serter::Doubly_linked_list< size_t > lsums;
  bool anotherList = true;
  size_t maxvalue = std::numeric_limits< size_t >::max();
  bool hasOverflow = false;
  while (anotherList)
  {
    size_t lsum = 0;
    anotherList = false;
    for (auto pair = pairsList.begin(); pair != pairsList.end(); ++pair)
    {
      if (!pair->second.is_empty())
      {
        if (anotherList)
        {
          output << " ";
        }
        output << pair->second.get_front();
        if (!hasOverflow && maxvalue - lsum > pair->second.get_front())
        {
          lsum += pair->second.get_front();
        }
        else
        {
          hasOverflow = true;
        }
        anotherList = true;
      }
    }
    if (hasOverflow)
    {
      output << "\n";
      throw std::overflow_error("overflow");
    }
    if (anotherList)
    {
      lsums.push(lsum);
      output << "\n";
    }
    for (auto pair = pairsList.begin(); pair != pairsList.end(); ++pair)
    {
      if (!pair->second.is_empty())
      {
        pair->second.pop_front();
      }
    }
  }
  if (lsums.is_empty())
  {
    output << "0";
  }
  else
  {
    bool anotherSum = false;
    for (auto sum = lsums.begin(); sum != lsums.end(); ++sum)
    {
      if (anotherSum)
      {
        output << ' ';
      }
      output << *sum;
      anotherSum = true;
    }
  }
}

int main()
{
  pairsOfList list;
  try
  {
    inputList(list, std::cin);
    outputList(list, std::cout);
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
