#include <iostream>
#include "inputOutput.hpp"
#include "list.hpp"

int main()
{
  List<std::pair<std::string, List<size_t>>> list;
  input(std::cin, list);
  list.reverse();
  List<size_t> sums;
  bool overflowFlag = false;
  try
  {
    outputNames(list);
    outputNums(list, sums, overflowFlag);
    sums.reverse();
    outputSums(sums);
    if (overflowFlag)
    {
      std::cerr << "overflow \n";
      return 1;
    }
  }
  catch (std::invalid_argument& e)
  {
    std::cout << "0\n";
    return 0;
  }
  catch (std::exception&e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
