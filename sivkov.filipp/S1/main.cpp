#include <iostream>
#include "inputOutput.hpp"
#include "list.hpp"

int main()
{
  using namespace sivkov;
  using pair = std::pair< std::string, List< size_t > >;
  List< pair > list;
  List< size_t > sums;
  try
  {
    input(std::cin, list);
    outputNames(list, std::cout);
    outputNums(list, sums, std::cout);
    outputSums(sums, std::cout);
    std::cout << "\n";
  }
  catch (const std::logic_error&)
  {
    std::cout << 0 << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
