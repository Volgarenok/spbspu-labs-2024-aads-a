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
  long long sum = 0;
  if (!lines.empty())
  {
    std::cout << lines.front().name;
  }
  auto iter_current = lines.cbegin() + 1;
  auto iter_end = lines.cend();
  while (iter_current != iter_end)
  {
    std::cout << " " << iter_current->name;
    ++iter_current;
  }
  std::cout << "\n"
  std::cout << sum;
  if (isBigNumberFound)
  {
    std::cerr << "Big number is found\n";
    return 1;
  }
  return 0;
}
