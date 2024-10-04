#include <iostream>
#include "list.hpp"
#include "input_output.hpp"

int main()
{
  vojuck::List< vojuck::paired_list > inputSequences;
  vojuck::inputLists(std::cin, inputSequences);

  if (inputSequences.empty())
  {
    std::cout << "0" << '\n';
    return 0;
  }
  if (inputSequences.getSize() == 1)
  {
    if (inputSequences.front().first != "")
    {
      if (inputSequences.front().second.empty())
        {
          std::cout << "0" << '\n';
          return 0;
        }
    }
  }

  auto it = inputSequences.cbegin();
  auto end = inputSequences.cend();
  if (it != end)
  {
    std::cout << it->first;
    ++it;
  }
  while (it != end)
  {
    std::cout << " " << it->first;
    ++it;
  }

  std::cout << '\n';

  vojuck::List< vojuck::List< size_t > > orderedSequences;
  vojuck::getOrderedLists(orderedSequences, inputSequences);

  vojuck::outputOrderedLists(orderedSequences);

  try
  {
    vojuck::List< size_t > sums;
    auto start = orderedSequences.cbegin();
    auto finish = orderedSequences.cend();
    while (start != finish)
    {
      size_t sum = 0;
      auto first = start->cbegin();
      auto last = start->cend();
      while (first != last)
      {
        sum += *first;
        ++first;
      }
      sums.push_back(sum);
      ++start;
    }
    auto sumIt = sums.cbegin();
    auto sumEnd = sums.cend();
    while (sumIt != sumEnd)
    {
      std::cout << *sumIt << " ";
      ++sumIt;
    }
    std::cout << '\n';
  }
  catch (...)
  {
    std::cerr << "Error: cannot compute sums" << '\n';
    return 1;
  }
  return 0;
}
