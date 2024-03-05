#include <iostream>
#include <utility>
#include <limits>
#include "list.hpp"
#include "iterator.hpp"
#include "inputList.hpp"

int main()
{
  using namespace strelyaev;
  size_t max_value = std::numeric_limits<size_t>::max();
  List< std::pair< std::string, List < size_t > > > list;
  try
  {
    makeSequence(std::cin, list);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
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

  bool all_empty = false;
  List< size_t > sums;
  while (!all_empty)
  {
    std::cout << "\n";
    all_empty = true;
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
      if (!it->second.empty())
      {
        all_empty = false;
        std::cout << it->second.front();
        if (max_value - sum > it->second.front())
        {
          sum += it->second.front();
        }
        else
        {
          std::cerr << "Overflow!\n";
          return 1;
        }
        it->second.pop_front();
      }
    }
    if (sum > 0)
    {
      sums.push_back(sum);
    }
  }

  for (auto it = sums.begin(); it != sums.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}
