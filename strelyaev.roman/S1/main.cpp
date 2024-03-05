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
  size_t sums_i = 0;
  List< size_t > sums;
  size_t max_element = 1;
  for (auto it = list.begin(); it != list.end(); it++)
  {
    size_t i = 0;
    for (auto inner_it = it->second.begin(); inner_it != it->second.end(); inner_it++)
    {
      i++;
      max_element = std::max(max_element, i);
    }
  }

  if (max_element != 1)
  {
    std::cout << "\n";
  }

  for (size_t i = 0; i < max_element; i++)
  {
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); it++)
    {
      if (!it->second.empty())
      {
        std::cout << it->second.front();
        auto temp_it = it;
        if (temp_it != list.end())
        {
          std::cout << " ";
        }
        sum += it->second.front();
        it->second.pop_front();
      }
    }
    std::cout << "\n";
    if (sums_i != max_element)
    {
      sums_i++;
      sums.push_back(sum);
    }
  }

  for (auto it = sums.begin(); it != sums.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}
