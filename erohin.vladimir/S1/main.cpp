#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "input_named_list.hpp"

int main()
{
  using namespace erohin;
  bool isBigNumberFound = false;
  List< named_list > lines;
  try
  {
    input_named_list(std::cin, lines);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation\n";
    return 2;
  }
  catch (const std::out_of_range &)
  {
    isBigNumberFound = true;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
  }

  if (!lines.empty())
  {
    std::cout << lines.front().name;
  }
  auto current = ++lines.cbegin();
  auto end = lines.cend();
  while (current != end)
  {
    std::cout << " " << current->name;
    ++current;
  }
  std::cout << "\n";

  List< ListConstIterator< int > > num_list_iter;
  current = lines.cbegin();
  try
  {
    while (current != end)
    {
      num_list_iter.push_front(current->number_list.cbegin());
      ++current;
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation\n";
    return 2;
  }
  num_list_iter.reverse();
  auto iter_end = lines.front().number_list.cend();
  List< long long > sums;
  while (!num_list_iter.empty())
  {
    sums.push_front(0ll);
    for (auto & iter: num_list_iter)
    {
      if (iter != iter_end)
      {
        std::cout << *iter << " ";
        sums.front() += *(iter++);
      }
    }
    std::cout << "\n";
    num_list_iter.remove(iter_end);
  }
  sums.reverse();
  for (auto elem: sums)
  {
    std::cout << elem << " ";
  }
  if (sums.empty())
  {
    std::cout << 0;
  }
  if (isBigNumberFound)
  {
    std::cerr << "Big number is found\n";
    return 1;
  }
  return 0;
}
