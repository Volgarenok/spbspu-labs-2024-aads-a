#include <iostream>
#include <cstddef>
#include <string>
#include "bdlist.hpp"
#include "iterator.hpp"
#include "input.hpp"

int main()
{
  using namespace ishmuratov;
  List< std::pair< std::string, List< size_t > > > pairs;
  inputList(pairs, std::cin);

  for (auto list = pairs.cbegin(); list != nullptr; ++list)
  {
    std::cout << list->first << " ";
  }
  std::cout << "\n";

  size_t sum = 0;
  bool anotherList = true;
  while (anotherList)
  {
    anotherList = false;
    for (auto pair = pairs.begin(); pair != nullptr; ++pair)
    {
      if (!pair->second.empty())
      {
        anotherList = true;
        std::cout << pair->second.front() << " ";
        sum += pair->second.front();
      }
    }
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
  std::cout << sum;
  return 0;
}
