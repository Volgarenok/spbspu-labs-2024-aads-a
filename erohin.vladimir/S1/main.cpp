#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "input_named_list.hpp"
#include "output_named_list.hpp"

int main()
{
  using namespace erohin;
  List< named_list > lines;
  List< List< uint64_t > > reformed_lines;
  List< uint64_t > sums;
  try
  {
    inputNamedListList(std::cin, lines);
    if (lines.empty())
    {
      std::cout << 0 << "\n";;
      return 0;
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation in list creation\n";
    return 2;
  }
  catch (const std::exception & e)
  {
    std::cerr << "Wrong number input\n";
  }
  try
  {
    printNames(std::cout, lines);
    std::cout << "\n";
    formOrderedNumLists(reformed_lines, lines);
    for (auto & cur_line: reformed_lines)
    {
      printList(std::cout, cur_line);
      std::cout << "\n";
    }
    formSumList(sums, reformed_lines);
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation in list handling\n";
    return 2;
  }
  printList(std::cout, sums);
  std::cout << "\n";
  return 0;
}
