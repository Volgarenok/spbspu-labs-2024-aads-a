#include <iostream>
#include <cstddef>
#include <string>
#include <limits>
#include <bdlist.hpp>
#include <iterator.hpp>
#include "input.hpp"

int main()
{
  using namespace ishmuratov;
  size_t maxvalue = std::numeric_limits< size_t >::max();
  List< std::pair< std::string, List< size_t > > > pairs;
  inputList(pairs, std::cin);

  for (auto list = pairs.begin(); list != pairs.end(); ++list)
  {
    if (list != pairs.begin())
    {
      std::cout << " ";
    }
    std::cout << list->first;
  }
  if (!pairs.empty())
  {
    std::cout << "\n";
  }
  List< size_t > lsums;
  bool anotherList = true;
  bool overflow = false;
  while (anotherList)
  {
    size_t lsum = 0;
    anotherList = false;
    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair)
    {
      if (!pair->second.empty())
      {
        if (anotherList)
        {
          std::cout << " ";
        }
        std::cout << pair->second.front();
        if (maxvalue - lsum > pair->second.front())
        {
          lsum += pair->second.front();
        }
        else
        {
          overflow = true;
        }
        anotherList = true;
      }
    }
    if (anotherList)
    {
       lsums.pushBack(lsum);
       std::cout << "\n";
    }
    for (auto pair = pairs.begin(); pair != pairs.end(); ++pair)
    {
      if (!pair->second.empty())
      {
         pair->second.popFront();
      }
    }
  }
  if (lsums.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  if (overflow)
  {
    std::cerr << "Overflow!\n";
    return 1;
  }
  for (auto sum = lsums.begin(); sum != lsums.end(); ++sum)
  {
    std::cout << *sum;
    if (*sum != lsums.back())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}
