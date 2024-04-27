#include <iostream>
#include <algorithm>
#include <limits>
#include <list.hpp>
#include "inputOperations.hpp"
#include "print.hpp"

int main()
{
  using namespace zakozhurnikova;
  using pair = std::pair< std::string, List< size_t > >;
  try
  {
    List< pair > list;
    readList(list, std::cin);
    printNames(list, std::cout);
    printByIndex(list, std::cout);
    printSums(list, std::cout);
    std::cout << '\n';
  }
  catch (const std::range_error& e)
  {
    return 1;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << "Overflow numbers!\n";
    return 1;
  }
  return 0;
}
