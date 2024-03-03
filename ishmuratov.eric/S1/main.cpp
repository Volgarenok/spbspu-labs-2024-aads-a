#include <iostream>
#include <cstddef>
#include <string>
#include <limits>
#include "bdlist.hpp"
#include "iterator.hpp"
#include "input.hpp"

int main()
{
  using namespace ishmuratov;

  size_t maxvalue = std::numeric_limits<size_t>::max();

  List< std::pair< std::string, List< size_t > > > pairs;
  inputList(pairs, std::cin);

  for (auto list = pairs.cbegin(); list != nullptr; ++list)
  {
    std::cout << list->first << " ";
  }
  std::cout << "\n";

  List< size_t > lsums;
  bool anotherList = true;
  bool overflow = false;
  while (anotherList)
  {
    size_t lsum = 0;
    anotherList = false;
    for (auto pair = pairs.begin(); pair != nullptr; ++pair)
    {
      //Iterator< size_t > num = pair->second.begin();
      if (!pair->second.empty())
      {
        anotherList = true;
        //std::cout << *num << " ";
        std::cout << pair->second.front() << " ";
        if (maxvalue - lsum > pair->second.front())
        {
          lsum += pair->second.front();
        }
        else
        {
          overflow = true;
        }
      }
    }
    lsums.pushBack(lsum);
    if (anotherList)
    {
       std::cout << "\n";
    }
    for (auto pair = pairs.begin(); pair != nullptr; ++pair)
    {
      if (!pair->second.empty())
      {
         pair->second.popFront();
      }
    }
  }
  if (overflow)
  {
    std::cerr << "Overflow!\n";
    return 1;
  }
  for (auto sum = lsums.begin(); sum != lsums.end(); ++sum)
  {
    std::cout << *sum << " ";
  }
  std::cout << "\n";
  return 0;
}
