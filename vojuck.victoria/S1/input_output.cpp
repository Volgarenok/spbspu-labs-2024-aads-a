#include <iostream>
#include <limits>
#include "input_output.hpp"

void vojuck::inputLine(std::istream & in, vojuck::paired_list & vertical)
{
  in >> vertical.first;
  size_t number;
  while (in >> number)
  {
    vertical.second.push_front(number);
    if (in.fail() && !in.eof())
    {
      in.clear();
     in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

void vojuck::inputLists(std::istream & in, vojuck::List< vojuck::paired_list > & result)
{
  while (!in.eof())
  {
    in.clear();
    vojuck::paired_list line;
    inputLine(in, line);
    result.push_front(line);
  }
}

void vojuck::getOrderedLists(vojuck::List< vojuck::List < size_t > > & result, vojuck::List< vojuck::paired_list > & listToOrder)
{
  using order_iterator = List< ConstIteratorList< size_t > >;
  order_iterator listIterator;
  auto start = listToOrder.cbegin();
  auto finish = listToOrder.cend();
  while (start != finish)
  {
    listIterator.push_front(start->second.cbegin());
    start++;
  }
  while (!listIterator.empty())
  {
    List< size_t > vertical;
    for (auto current : listIterator)
    {
      if (current != nullptr)
      {
        vertical.push_front(*current);
        current++;
      }
    }
    if (!vertical.empty())
    {
      result.push_front(vertical);
      listIterator.pop_front();
    }
  }
}


void vojuck::outputOrderedLists(vojuck::List< vojuck::List< size_t > > & orderedList)
{
  auto start = orderedList.cbegin();
  auto finish = orderedList.cend();
  while (start != finish)
  {
    auto first = start->cbegin();
    auto last = start->cend();
    while (first != last)
    {
      std::cout << *first << " ";
      first++;
    }
    std::cout << "\n";
    start++;
  }
}
