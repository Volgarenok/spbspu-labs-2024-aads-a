#include <iostream>
#include <stdexcept>
#include "outputResults.hpp"
#include "listManipulations.hpp"
#include "inputList.hpp"

int main()
{
  using namespace isaychev;
  using stringListPair = std::pair< std::string, List< unsigned long long int > >;
  List< stringListPair > mainList;
  try
  {
    inputList(std::cin, mainList);

    reverseAll(mainList);

    size_t upperBorder = getMaxFwdElemNum(mainList) + 1;
    size_t numOfPairs = getElemNum(mainList);

    if (upperBorder > 1)
    {
      outputNames(std::cout, mainList);
      outputNumbers(std::cout, mainList);
      outputSums(std::cout, mainList);
    }
    else if (upperBorder == 1 && numOfPairs == 1)
    {
      std::cout << mainList.front().first << "\n" << 0 << "\n";
    }
    else if (numOfPairs == 0)
    {
      std::cout << 0 << "\n";
    }

    reverseAll(mainList);
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
