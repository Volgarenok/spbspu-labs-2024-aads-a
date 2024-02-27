#include <iostream>
#include <string>
#include <cstring>
#include "forward_list.hpp"
#include "forward_list_iterator.hpp"

int main()
{
  using namespace zaitsev;
  using pair = std::pair<std::string, ForwardList<unsigned long long>>;
  using FLI = ForwardListIterator<unsigned long long>;
  ForwardList<pair> list;
  std::string input;
  std::cin >> input;
  while (std::cin)
  {
    list.push_front({ input, ForwardList<unsigned long long>() });
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
  list.reverse();
  ForwardList<std::pair<FLI, FLI>> beg_iterators;
  for (ForwardListIterator<pair> i = list.begin(); i != list.end(); ++i)
  {
    i->second.reverse();
    if (i != list.begin())
    {
      std::cout << " ";
    }
    std::cout << i->first;
    beg_iterators.push_front({ i->second.begin(), i->second.end() });
  }
  beg_iterators.reverse();
  std::cout << '\n';
  ForwardList<unsigned long long> sums;
  unsigned long long sum = 1;
  while (sum)
  {
    sum = 0;
    for (ForwardListIterator<std::pair<FLI, FLI>> i = beg_iterators.begin(); i != beg_iterators.end(); ++i)
    {
      if (i->first != i->second)
      {
        std::cout << *(i->first);
        sum += *(i->first);
        ++i->first;
        if (i->first != i->second)
        {
          std::cout << '\n';
        }
      }
    }
    if (sum)
    {
      std::cout << "\n";
      sums.push_front(sum);
    }
  }
  sums.reverse();

  for (FLI i = sums.begin(); i != sums.end(); ++i)
  {
    if (i != sums.begin())
    {
      std::cout << " ";
    }
    std::cout << *i;
  }

  return 0;
}
