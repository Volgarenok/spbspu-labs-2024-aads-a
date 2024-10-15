#include <iostream>
#include <cassert>
#include <limits>

#include "list.hpp"

int main()
{
  using pair_t = std::pair< std::string, kovtun::List< size_t > >;
  kovtun::List< pair_t > sequences;

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

  size_t maxSize = 0;
  for (auto seq = sequences.cbegin(); seq != sequences.cend(); ++seq)
  {
    if (maxSize < seq->second.size())
    {
      maxSize = seq->second.size();
    }
  }

  for (auto seq = sequences.cbegin(); seq != sequences.cend(); ++seq)
  {
    std::cout << seq->first;
    if (seq++ != sequences.cend())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";


  kovtun::List< size_t > sums;
  kovtun::List< kovtun::List< size_t > > output;

  bool hasOverflow = false;
  size_t sum = 0;
  for (size_t l = 0; l < maxSize; l++)
  {
    kovtun::List< size_t > row;
    for (auto seq = sequences.cbegin(); seq != sequences.cend(); ++seq)
    {
      if (!seq->second.empty())
      {
        size_t val = *seq->second.cbegin();
        row.push_back(val);
        seq->second.pop_front();

        if (val > std::numeric_limits< size_t >::max() - sum)
        {
          hasOverflow = true;
          continue;
        }
        sum += val;
      }
    }
    sums.push_back(sum);
    output.push_back(row);
  }

  if (hasOverflow)
  {
    std::cerr << "overflow\n";
    return 1;
  }

  for (auto row = output.cbegin(); row != output.cend(); ++row)
  {
    for (auto num = row->cbegin(); num != row->cend(); ++num)
    {
      std::cout << *num;
      if (num++ != row->cend())
      {
        std::cout << " ";
      }
    }
  }
  std::cout << "\n";

  if (sums.empty())
  {
    sums.push_back(0);
  }
  for (auto it = sums.cbegin(); it != sums.cend(); ++it)
  {
    std::cout << *it;
    if (it++ != sums.cend())
    {
      std::cout << " ";
    }
  }

  return 0;
}
