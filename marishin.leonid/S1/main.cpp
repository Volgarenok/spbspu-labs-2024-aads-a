#include <iostream>
#include <limits>

#include "input.hpp"
#include <linkedList.hpp>

int main()
{
  using namespace marishin;
  constexpr size_t maxvalue = std::numeric_limits< size_t >::max();
  LinkedList< std::pair< std::string, LinkedList< size_t > > > pairs;
  inputList(pairs, std::cin);

  auto iter = pairs.begin();
  auto end = pairs.end();
  while (iter != end)
  {
    std::cout << iter->first;
    if (++iter != end)
    {
      std::cout << " ";
    }
  }
  if (!pairs.empty())
  {
    std::cout << "\n";
  }
  LinkedList< size_t > lst;
  bool overflow = false;
  bool emptyList = true;
  while (emptyList)
  {
    size_t sum = 0;
    emptyList = false;
    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair)
    {
      if (!pair->second.empty())
      {
        if (emptyList)
        {
          std::cout << " ";
        }
        std::cout << pair->second.front();
        if (maxvalue - sum > pair->second.front())
        {
          sum += pair->second.front();
        }
        else
        {
          overflow = true;
        }
        emptyList = true;
      }
    }
    if (emptyList)
    {
      lst.push_back(sum);
      std::cout << "\n";
    }
    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair)
    {
      if (!pair->second.empty())
      {
        pair->second.pop_front();
      }
    }
  }
  if (lst.empty())
  {
    std::cout << '0';
  }
  if (overflow)
  {
    std::cerr << "Overflow!\n";
    return 1;
  }
  for (auto sum = lst.begin(); sum != lst.end(); ++sum)
  {
    std::cout << *sum;
    if (*sum != lst.back())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}
