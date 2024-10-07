#include "input_output.hpp"

#include <sstream>
#include <vector>
#include <iostream>
#include <limits>

void vojuck::inputLine(std::istream & in, vojuck::paired_list & vertical)
{
  in >> vertical.first;
  std::string number;
  if (in.peek() == '\n')
  {
    return;
  }
  while(in >> number)
  {
    try
    {
      vertical.second.push_back(std::stoull(number));
    }
    catch (std::out_of_range &)
    {
      in.clear();
      throw std::overflow_error("the value is kinda big hz");
    }
    if (in.peek() == '\n')
    {
      break;
    }
  }
}

void vojuck::inputLists(std::istream & in, vojuck::List< vojuck::paired_list > & result)
{
  while (!in.eof())
  {
    vojuck::paired_list line;
    try
    {
      inputLine(in, line);
    }
    catch (std::overflow_error & e)
    {
      line.first = "";
      line.second.clear();
      std::cerr << e.what() << "\n";
    }
    if (!line.first.empty())
    {
      result.push_back(line);
    }
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
