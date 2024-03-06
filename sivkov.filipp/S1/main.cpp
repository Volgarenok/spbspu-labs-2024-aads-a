#include <iostream>
#include "inputOutput.hpp"
#include "list.hpp"

int main()
{
  List<std::pair<std::string, List<size_t>>> list;
  list.reverse();
  input(std::cin, list);
  List<size_t> sums;
  try
  {
    outputNames(list);
    outputNums(list, sums);
    sums.reverse();
    outputSums(sums);
  }
  catch (std::invalid_argument& e)
  {
    std::cout << "0\n";
    return 0;
  }
  catch (std::out_of_range& e)
  {
    std::cerr << "overflow\n";
    return 1;
  }

  return 0;
}
