#include <iostream>
#include <limits>

#include <constiterator.hpp>
#include <iterator.hpp>
#include <list.hpp>

#include "inputlist.hpp"

int main()
{
  using namespace gladyshev;
  List< std::pair< std::string, List< size_t > > > sequences;
  readSequence(std::cin, sequences);
  if (sequences.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  sequences.reverse();
  std::cout << sequences.front().first;
  for (auto it = ++sequences.cbegin(); it != sequences.cend(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";
  bool overflow = false;
  size_t sum = 0;
  size_t counter = 0;
  bool moreData = true;
  List< size_t > listOfNums;
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    it->second.reverse();
  }
  while (moreData)
  {
    moreData = false;
    for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
    {
      auto itr = it->second.cbegin();
      for (size_t i = 0; i < counter; ++i)
      {
        if (itr != it->second.cend())
        {
          ++itr;
        }
      }
      if (itr != it->second.cend())
      {
         if (moreData)
         {
           std::cout << " ";
         }
         if (std::numeric_limits< size_t >::max() - sum >= *itr)
         {
           sum += *itr;
         }
         else
         {
           overflow = true;
         }
         std::cout << *itr;
         moreData = true;
      }
    }
    if (moreData)
    {
      std::cout << "\n";
      listOfNums.push_front(sum);
      sum = 0;
    }
    ++counter;
  }
  if (overflow)
  {
    std::cerr << "overflow detected\n";
    return 1;
  }
  if (listOfNums.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  listOfNums.reverse();
  std::cout << listOfNums.front();
  for (auto it = ++listOfNums.cbegin(); it != listOfNums.cend(); ++it)
  {
    std::cout << " " << *it;
  }
  std::cout << "\n";
  return 0;
}
