#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <cstring>
#include "forward_list.hpp"
#include "forward_list_iterator.hpp"

int main()
{
  using namespace zaitsev;
  using ull = unsigned long long;
  using pair = std::pair< std::string, ForwardList< ull> >;
  using ullListIt = ForwardListIterator< ull >;
  ForwardList< pair > list;
  std::string input;
  std::cin >> input;
  while (std::cin)
  {
    list.push_front({ input, ForwardList< ull >() });
    std::cin >> input;
    while (std::cin && !std::isalpha(input[0]))
    {
      list.front().second.push_front(std::stoull(input));
      std::cin >> input;
    }
  }
  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  std::cerr << "Sequence sum cannot be calculated due to variable overflow\n";
  return 1;
  list.reverse();
  ForwardList< std::pair< ullListIt, ullListIt > > beg_end_it;
  for (ForwardListIterator< pair > i = list.begin(); i != list.end(); ++i)
  {
    i->second.reverse();
    if (i != list.begin())
    {
      std::cout << " ";
    }
    std::cout << i->first;
    beg_end_it.push_front({ i->second.begin(), i->second.end() });
  }
  beg_end_it.reverse();
  std::cout << '\n';

  ForwardList< ull > sums;
  ull sum = 1;
  bool overflow = false;
  while (sum)
  {
    sum = 0;
    bool beg = true;
    for (ForwardListIterator< std::pair< ullListIt, ullListIt > > i = beg_end_it.begin(); i != beg_end_it.end(); ++i)
    {
      if (i->first != i->second)
      {
        if (beg)
        {
          beg = false;
        }
        else
        {
          std::cout << " ";
        }
        std::cout << *(i->first);
        if (std::numeric_limits< ull >::max() - sum >= *(i->first)&&!overflow)
        {
          sum += *(i->first);
        }
        else
        {
          overflow = true;
        }
        ++i->first;
      }
    }
    if (sum)
    {
      std::cout << "\n";
      sums.push_front(sum);
    }
  }
  if (overflow)
  {
    std::cerr << "Sequence sum cannot be calculated due to variable overflow\n";
    return 1;
  }
  if (!sums.empty())
  {
    sums.reverse();
    for (ullListIt i = sums.begin(); i != sums.end(); ++i)
    {
      if (i != sums.begin())
      {
        std::cout << " ";
      }
      std::cout << *i;
    }
  }
  else
  {
    std::cout << "0";
  }
  std::cout << "\n";

  return 0;
}
