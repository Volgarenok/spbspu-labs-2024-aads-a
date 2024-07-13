#include <iostream>
#include <algorithm>
#include <limits>
#include "List.hpp"
#include "InputSequence.hpp"
#include "OutputSequence.hpp"

int main()
{
  using namespace vyzhanov;
  using pair = std::pair< std::string, List< size_t > >;
  try
  {
    List< pair > list;
    inputSequence(list, std::cin);
    outputNames(list, std::cout);
    outputNums(list, std::cout);
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
