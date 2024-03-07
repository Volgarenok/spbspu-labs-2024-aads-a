#include "output_named_list.hpp"
#include <iostream>
#include "named_number_list.hpp"

std::ostream & erohin::printNames(std::ostream & output, const List< named_list > & list)
{
  if (!list.empty())
  {
    output << list.front().name;
  }
  auto current = ++list.cbegin();
  auto last = list.cend();
  while (current != last)
  {
    output << " " << current->name;
    ++current;
  }
  return output;
}

std::ostream & erohin::printSums(std::ostream & output, const List< long long > & sum)
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
  List< ListConstIterator< int > > iter_list;
  auto current = list.cbegin();
  auto last = list.cend();
  size_t max_count = 0;
  while (current != last)
  {
    iter_list.push_front(current->number_list.cbegin());
    ++current;
  }
  iter_list.reverse();
  List< long long > sum;
  auto iter_end = list.front().number_list.cend();
  while (!iter_list.empty())
  {
    sum.push_front(0ll);
    size_t count = 0;
    for (auto & iter: iter_list)
    {
      if (iter != iter_end)
      {
        std::cout << (count ? " " : "") << *iter;
        sum.front() += *iter;
        ++iter;
        ++count;
      }
    }
    iter_list.remove(iter_end);
    if (!(max_count == count && iter_list.empty()))
    {
      std::cout << "\n";
    }
  }
  sum.reverse();
  printSums(output, sum);
  return output;
}
