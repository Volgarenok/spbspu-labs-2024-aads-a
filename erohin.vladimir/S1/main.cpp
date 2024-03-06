#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "input_named_list.hpp"

int main()
{
  using namespace erohin;
  List< named_list > lines;
  try
  {
    input_named_list(std::cin, lines);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation\n";
    return 1;
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
  std::cout << compare(lines.cbegin()->number_list, (lines.cbegin() + 1)->number_list);
  std::cout << sum;
  return 0;
}
