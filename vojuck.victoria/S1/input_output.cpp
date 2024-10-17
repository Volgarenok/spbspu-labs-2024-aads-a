#include "input_output.hpp"

#include <sstream>
#include <vector>
#include <iostream>
#include <limits>

void vojuck::inputLine(std::istream & in, vojuck::paired_list & vertical)
{
    std::string line;
  if (!std::getline(in, line))
  {
    return;
  }
  std::istringstream iss(line);
  iss >> vertical.first;
  size_t number;
  while(iss >> number)
  {
    if (number > std::numeric_limits< size_t >::max())
    {
      throw std::overflow_error("The value is too big\n");
    }
    vertical.second.push_back(number);
  }
}

void vojuck::inputLists(std::istream & in, vojuck::List< vojuck::paired_list > & result)
{
  while (!in.eof())
  {
    vojuck::paired_list line;
    inputLine(in, line);
    if (line.first.empty())
    {
      break;
    }
    result.push_back(line);
  }
}

void vojuck::getOrderedLists(vojuck::List< vojuck::List < size_t > > & result, vojuck::List< vojuck::paired_list > & listToOrder)
{
  std::vector< vojuck::ConstIteratorList< size_t > > iterators;
  std::vector< vojuck::ConstIteratorList< size_t > > ends;

  auto start = listToOrder.cbegin();
  auto finish = listToOrder.cend();

  while (start != finish)
  {
    iterators.push_back(start->second.cbegin());
    ends.push_back(start->second.cend());
    start++;
  }
  bool done = false;
  while (!done)
  {
    done = true;
    vojuck::List< size_t > newSequence;
    for (size_t i = 0; i < iterators.size(); ++i)
    {
      if (iterators[i] != ends[i])
      {
        newSequence.push_back(*iterators[i]);
        ++iterators[i];
        done = false;
      }
    }
    if (!newSequence.empty())
    {
      result.push_back(newSequence);
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
    if (first != last)
    {
      std::cout << *first;
      first++;
    }
    while (first != last)
    {
      std::cout << " " << *first;
      first++;
    }
    std::cout << "\n";
    start++;
  }
}
