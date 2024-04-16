#include <iostream>
#include <utility>
#include <limits>
#include <list/list.hpp>
#include <list/iterator.hpp>
#include "inputList.hpp"

int main()
{
  using namespace strelyaev;
  List< std::pair< std::string, List < size_t > > > list;
  try
  {
    makeSequence(std::cin, list);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }
  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto it = list.begin(); it != list.end(); it++)
  {
    std::cout << it->first;
    auto temp_it = it;
    if (++temp_it != list.end())
    {
      std::cout << " ";
    }
  }

  size_t max_element = 0;
  for (auto it = list.cbegin(); it != list.cend(); it++)
  {
    size_t i = 0;
    if (it->second.empty())
    {
      continue;
    }
    for (auto inner_it = it->second.cbegin(); inner_it != it->second.cend(); inner_it++)
    {
      i++;
      max_element = std::max(max_element, i);
    }
  }

  List< size_t > sums;
  bool overflow = false;
  size_t max_sizet = std::numeric_limits< size_t >::max();
  size_t sums_i = 0;
  if (max_element != 1)
  {
    std::cout << "\n";
  }

  for (size_t i = 0; i < max_element; i++)
  {
    size_t sum = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
      if (!it->second.empty())
      {
        if (sum > 0 || overflow)
        {
          std::cout << " ";
        }
        std::cout << it->second.front();
        if (sum < max_sizet - it->second.front())
        {
          sum += it->second.front();
        }
        else
        {
          overflow = true;
        }
        it->second.pop_front();
      }
    }
    std::cout << "\n";

    if (overflow)
    {
      std::cerr << "Overflow\n";
      return 1;
    }
    if (sums_i != max_element)
    {
      sums_i++;
      sums.push_back(sum);
    }
  }

  if (sums.empty())
  {
    sums.push_front(0);
  }

  for (auto it = sums.begin(); it != sums.end(); it++)
  {
    std::cout << *it;
    auto temp_it = it;
    if (++temp_it != sums.end())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}
