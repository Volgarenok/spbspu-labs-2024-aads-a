#include <iostream>
#include "inputOutput.hpp"
#include <list.hpp>

int main()
{
  using namespace sivkov;
  using pair = std::pair< std::string, List< size_t > >;
  List< pair > list;

  try
  {
    input(std::cin, list);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }

  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  list.reverse();

  outputNames(list, std::cout);
  std::cout << '\n';
  List< size_t > sums;
  try
  {
    outputNums(list, sums);
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << "Overflow\n";
    return 1;
  }

  sums.reverse();
  outputSums(sums, std::cout);
  std::cout << '\n';
  return 0;
}
