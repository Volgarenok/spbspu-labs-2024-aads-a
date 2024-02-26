#include <iostream>
#include <string>
#include <cstring>
#include "forward_list.hpp"
#include "forward_list_iterator.hpp"

int main()
{
  using namespace zaitsev;
  using pair = std::pair<std::string, ForwardList<unsigned long>>;
  using FLI = ForwardListIterator<unsigned long>;
  ForwardList<pair> list;
  std::string input;
  std::cin >> input;
  while (std::cin)
  {
    list.push_front({ input, ForwardList<unsigned long>() });
    std::cin >> input;
    while (std::cin && !std::isalpha(input[0]))
    {
      list.front().second.push_front(std::stoul(input));
      std::cin >> input;
    }
  }
  ForwardList<pair> reversed_list;
  ForwardList<std::pair<FLI, FLI>> beg_iterators;
  for (ForwardListIterator<pair> i = list.begin(); i != list.end(); ++i)
  {
    beg_iterators.push_front({ i->second.begin(), i->second.end() });
    reversed_list.push_front(*i);
  }
  for (ForwardListIterator<pair> i = reversed_list.begin(); i != reversed_list.end(); ++i)
  {
    if (i != reversed_list.begin())
    {
      std::cout << " ";
    }
    std::cout << i->first;
  }
  std::cout << '\n';
  ForwardList<unsigned long> sums;
  unsigned long sum = 1;
  while (sum)
  {
    sum = 0;
    for (ForwardListIterator<std::pair<FLI, FLI>> i = beg_iterators.begin(); i != beg_iterators.end(); ++i)
    {
      if (i->first != i->second)
      {
        std::cout << *(i->first) << " ";
        sum += *(i->first);
        ++i->first;
      }
    }
    if (sum)
    {
      std::cout << "\n";
      sums.push_front(sum);
    }
  }
  ForwardList<unsigned long> reversed_sums;
  for (FLI i = sums.begin(); i != sums.end(); ++i)
  {
    reversed_sums.push_front(*i);
  }
  for (FLI i = reversed_sums.begin(); i != reversed_sums.end(); ++i)
  {
    std::cout << *i << " ";
  }

  return 0;
}
