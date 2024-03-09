#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "input_named_list.hpp"
#include "output_named_list.hpp"

int main()
{
  using namespace erohin;
  bool isBigNumberFound = false;
  List< named_list > lines;
  List< List< int_type > > reformed_lines;
  List< long_type > sums;
  try
  {
    inputNamedList(std::cin, lines);
    if (lines.empty())
    {
      std::cout << 0 << "\n";;
      return 0;
    }
  }
  catch (const std::out_of_range &)
  {
    isBigNumberFound = true;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation\n";
    return 2;
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
  }
  try
  {
    printNames(std::cout, lines);
    std::cout << "\n";
    formOrderedNumLists(reformed_lines, lines);
    for (auto cur_line: reformed_lines)
    {
      printList(std::cout, cur_line);
      std::cout << "\n";
    }
    formSumList(sums, reformed_lines);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad allocation\n";
    return 2;
  }
  if (isBigNumberFound)
  {
    std::cerr << "Big number is found\n";
    return 1;
  }
  else
  {
    printList(std::cout, sums);
    std::cout << "\n";
  }
  return 0;
}
