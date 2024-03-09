#include "output_named_list.hpp"
#include <iostream>

std::ostream & erohin::printNames(std::ostream & output, const List< named_list > & list)
{
  if (!list.empty())
  {
    output << list.front().first;
  }
  else
  {
    return output;
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

void erohin::formOrderedNumLists(List < List< int_type > > & result, const List< named_list > & list)
{
  result.clear();
  using iterator_list = List< ListConstIterator< int_type > >;
  iterator_list iters;
  auto current = list.cbegin();
  auto last = list.cend();
  while (current != last)
  {
    iters.push_front(current->second.cbegin());
    ++current;
  }
  iters.reverse();
  auto iter_to_delete = list.front().second.cend();
  auto end_line_iter = result.cbegin();
  while (!iters.empty())
  {
    List< int_type > current_number_line;
    for (auto & cur_iter: iters)
    {
      if (cur_iter != iter_to_delete)
      {
        current_number_line.push_front(*cur_iter);
        ++cur_iter;
      }
    }
    current_number_line.reverse();
    iters.remove(iter_to_delete);
    if (!current_number_line.empty())
    {
      result.push_front(std::move(current_number_line));
    }
  }
  result.reverse();
}

void erohin::formSumList(List< long_type > & result, const List < List< int_type > > & list)
{
  result.clear();
  if (list.empty())
  {
    result.push_front(0);
    return;
  }
  for (auto num_list: list)
  {
    long_type sum = 0;
    for (auto num: num_list)
    {
      sum += num;
    }
    result.push_front(sum);
  }
  result.reverse();
}
