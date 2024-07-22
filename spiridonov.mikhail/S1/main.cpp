#include <iostream>
#include <string>
#include <utility>
#include "forward_list.hpp"
#include "functions.hpp"

using namespace spiridonov;

int main()
{
  List<nameList> sequences = {};

  try
  {
    sequences = input(std::cin);
  }
  catch (std::invalid_argument&)
  {
    std::cout << '0' << "\n";
    return 0;
  }
  catch (std::overflow_error& ex)
  {
    std::cout << ex.what() << "\n";
    return 1;
  }

  bool hasNumbers = false;
  for (const auto& sequence : sequences)
  {
    if (!sequence.second.is_empty())
    {
      hasNumbers = true;
      break;
    }
  }

  if (!hasNumbers)
  {
    for (const auto& sequence : sequences)
    {
      if (sequence.second.is_empty())
      {
        std::cout << sequence.first << "\n" << '0' << "\n";
      }
    }
    return 0;
  }
  if (!sequences.is_empty())
  {
    auto it = sequences.begin();
    if (it != sequences.end())
    {
      std::cout << it->first;
      ++it;
    }
    for (; it != sequences.end(); ++it)
    {
      std::cout << ' ' << it->first;
    }
    std::cout << "\n";
  }

  List<List<size_t>> nums;
  bool empty = false;
  while (!empty)
  {
    empty = true;
    List<size_t> cumulate;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      if (!it->second.is_empty())
      {
        empty = false;
        cumulate.push_back(it->second.pop_front());
      }
    }
    if (empty == false)
    {
      nums.push_back(cumulate);
    }
  }

  for (auto it = nums.begin(); it != nums.end(); ++it)
  {
    printListValues(*it);
  }

  try
  {
    List<size_t> sum;
    for (auto it = nums.begin(); it != nums.end(); ++it)
    {
      sum.push_back(sumListValues(*it));
    }
    printListValues(sum);
  }
  catch (std::exception&)
  {
    std::cerr << "Error: Calculation of sum is not possible." << "\n";
    return 1;
  }
  return 0;
}
