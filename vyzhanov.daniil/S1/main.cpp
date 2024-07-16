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
    if (list.empty())
    {
      std::cout << 0 << "\n";
      return 0;
    }
    outputNames(list, std::cout);
    outputNums(list, std::cout);
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
