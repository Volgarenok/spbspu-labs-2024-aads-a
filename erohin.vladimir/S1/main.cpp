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
  auto current = lines.cbegin() + 1;
  auto end = lines.cend();
  while (current != end)
  {
    std::cout << " " << iter_current->name;
    ++current;
  }
  std::cout << "\n";

  List< named_list.number_list::const_iterator > iter;
  current = lines.cbegin();
  end = lines.cend();
  while (iter_current != iter_end)
  {
    iter.push_front((iter_current++)->number_list.cbegin());
  }
  iter.reverse();
  auto iter_end = lines.front().number_list.front().cend();

  List< long long > sums({ 0 });
  if (isBigNumberFound)
  {
    std::cerr << "Big number is found\n";
    return 1;
  }
  return 0;
}
