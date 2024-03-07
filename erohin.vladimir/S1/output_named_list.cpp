#include "output_named_list.hpp"
#include <iostream>

std::ostream & erohin::printNames(std::ostream & output, const List< named_list > & list)
{
  if (!list.empty())
  {
    output << list.front().first;
  }
  auto current = ++list.cbegin();
  auto last = list.cend();
  while (current != last)
  {
    output << " " << current->first;
    ++current;
  }
  return output;
}

std::ostream & erohin::printSums(std::ostream & output, const List< size_t > & sum)
{
  if (!sum.empty())
  {
    output << sum.front();
  }
  else
  {
    return (output << 0);
  }
  auto current = ++sum.cbegin();
  auto last = sum.cend();
  while (current != last)
  {
    output << " " << *current;
    ++current;
  }
  return output;
}

std::ostream & erohin::printElementsAndSums(std::ostream & output, const List< named_list > & list)
{
  using iterator_list = List< ListConstIterator< size_t > >;
  iterator_list iters;
  auto current = list.cbegin();
  auto last = list.cend();
  size_t max_count = 0;
  while (current != last)
  {
    iters.push_front(current->second.cbegin());
    ++current;
  }
  iters.reverse();
  List< size_t > sum;
  auto iter_end = list.front().second.cend();
  while (!iters.empty())
  {
    sum.push_front(0);
    size_t count = 0;
    for (auto & cur_iter: iters)
    {
      if (cur_iter != iter_end)
      {
        output << (count ? " " : "") << *cur_iter;
        sum.front() += *cur_iter;
        ++cur_iter;
        ++count;
      }
    }
    iters.remove(iter_end);
    if (!(max_count == count && iters.empty()))
    {
      output << "\n";
    }
  }
  sum.reverse();
  printSums(output, sum);
  return output;
}
