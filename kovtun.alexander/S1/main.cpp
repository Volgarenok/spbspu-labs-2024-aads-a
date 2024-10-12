#include <iostream>
#include <cassert>
#include <limits>

#include "list.hpp"

int main()
{
  using pair_t = std::pair< std::string, kovtun::List< size_t > >;
  auto sequences = kovtun::List< pair_t >();

  std::string stub;
  while(std::cin >> stub)
  {
    if (stub.empty())
    {
      break;
    }

    auto nums = kovtun::List< size_t >();
    size_t n = 0;
    while (std::cin >> n)
    {
      nums.push_back(n);
    }
    pair_t pair = std::make_pair(stub, nums);
    sequences.push_back(pair);

    if (!std::cin.eof())
    {
      std::cin.clear();
    }
  }

  if (sequences.empty())
  {
    std::cout << 0 << "\n";
    return 0;
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
        if (val > std::numeric_limits< size_t >::max() - sum)
        {
          std::cerr << "overflow" << "\n";
          return 1;
        }
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
