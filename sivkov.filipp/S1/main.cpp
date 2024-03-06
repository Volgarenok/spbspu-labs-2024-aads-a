#include <limits>
#include "inputOutput.hpp"
#include "list.hpp"
#include "outputNums.hpp"

int main()
{
  List<std::pair<std::string, List<size_t>>> list;
  input(std::cin, list);
  list.reverse();
  List<size_t> sums;
  try
  {
    outputNames(list);
    addnum(list, sums);
    sums.reverse();
    outputSums(sums);
  }
  catch (std::invalid_argument& e)
  {
    std::cout << 0;
    return 0;
  }
  catch (std::out_of_range& e)
  {
    std::cerr << "OverFlow";
    return 1;
  }

  return 0;
}
