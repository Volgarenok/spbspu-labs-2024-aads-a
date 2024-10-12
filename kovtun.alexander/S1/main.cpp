#include <iostream>
#include <cassert>

#include "list.hpp"

int main()
{
  using pair = std::pair< std::string, kovtun::List< size_t > >;
  kovtun::List< pair > sequences;

  std::string stub;
  while(!std::cin.eof())
  {
    std::cin.clear();
    std::cin >> stub;
    if (stub.empty())
    {
      break;
    }

    kovtun::List< size_t > list;
    size_t n = 0;
    while (std::cin >> n)
    {
      list.push_back(n);
    }
    sequences.push_back({ stub, list });
  }

  size_t maxSeq = 0;
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    size_t size = it->second.size();
    if (maxSeq < size)
    {
      maxSeq = it->second.size();
    }
  }

  for (auto seq = sequences.cbegin(); seq != sequences.cend(); ++seq)
  {
    std::cout << seq->first << " ";
  }
  std::cout << "\n";

  kovtun::List< size_t > sums;
  for (size_t l = 0; l < maxSeq; l++)
  {
    size_t sum = 0;
    for (auto seq = sequences.cbegin(); seq != sequences.cend(); ++seq)
    {
      if (!seq->second.empty())
      {
        size_t val = *seq->second.cbegin();
        sum += val;
        std::cout << val << " ";
        seq->second.pop_front();
      }
    }
    std::cout << "\n";
    sums.push_back(sum);
  }

  for (auto it = sums.cbegin(); it != sums.cend(); ++it)
  {
    std::cout << *it << " ";
  }

  return 0;
}
