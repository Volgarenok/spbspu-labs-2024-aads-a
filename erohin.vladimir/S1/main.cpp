#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "input_named_list.hpp"
#include "output_named_list.hpp"
#include "named_number_list.hpp"

int main()
{
  using namespace erohin;
  bool isBigNumberFound = false;
  List< named_list > lines;
  try
  {
    inputNamedList(std::cin, lines);
    if (lines.empty())
    {
      std::cout << 0 << "\n";
    }
    else
    {
      printNames(std::cout, lines);
      std::cout << "\n";
      printElementsAndSums(std::cout, lines);
      std::cout << "\n";
    }
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
  if (isBigNumberFound)
  {
    std::cerr << "Big number is found\n";
    return 1;
  }
  return 0;
}
