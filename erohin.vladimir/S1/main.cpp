#include <iostream>
#include <stdexcept>
#include "list.hpp"
#include "input_named_list.hpp"
#include "output_named_list.hpp"
#include "named_number_list.hpp"

int main()
{
  using namespace erohin;
  List< named_list > lines;
  try
  {
    inputNamedList(std::cin, lines);
    if (!lines.empty())
    {
      printNames(std::cout, lines);
      std::cout << "\n";
      printElementsAndSums(std::cout, lines);
      std::cout << "\n";
    }
    else
    {
      std::cerr << "0\n";
    }
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "Big number is found\n";
    return 1;
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
  return 0;
}
