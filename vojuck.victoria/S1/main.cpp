#include <iostream>
#include "list.hpp"
#include "input_output.hpp"

int main()
{
  vojuck::List< vojuck::paired_list > inputSequences;
  vojuck::inputLists(std::cin, inputSequences);

  if (inputSequences.empty())
  {
    std::cout << "0" << std::endl;
    return 0;
  }

  auto it = inputSequences.cbegin();
  auto end = inputSequences.cend();
  while (it != end)
  {
    std::cout << it->first << " ";
    ++it;
  }
  std::cout << '\n';

  vojuck::List< vojuck::List< size_t > > orderedSequences;
  vojuck::getOrderedLists(orderedSequences, inputSequences);

  vojuck::outputOrderedLists(orderedSequences);

  try
  {
    vojuck::List< size_t > sums;
    auto seqIt = orderedSequences.cbegin();
    auto seqEnd = orderedSequences.cend();
    while (seqIt != seqEnd)
    {
      size_t sum = 0;
      auto numIt = seqIt->cbegin();
      auto numEnd = seqIt->cend();
      while (numIt != numEnd)
      {
        sum += *numIt;
        ++numIt;
      }
      sums.push_back(sum);
      ++seqIt;
    }
    auto sumIt = sums.cbegin();
    auto sumEnd = sums.cend();
    while (sumIt != sumEnd)
    {
      std::cout << *sumIt << " ";
      ++sumIt;
    }
    std::cout << std::endl;
  }
  catch (...)
  {
    std::cerr << "Error: cannot compute sums" << std::endl;
    return 1;
  }

  return 0;
}
