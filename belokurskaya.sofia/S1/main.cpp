#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "readSequences.hpp"
#include "resultsPrinter.hpp"

int main()
{
  using namespace belokurskaya;
  try
  {
    List< std::pair< std::string, List< size_t > > > sequences;

    readSequences(std::cin, sequences);
    if (sequences.empty())
    {
      std::cout << 0 << '\n';
      return 0;
    }

    printNames(std::cout, sequences);
    std::cout << '\n';

    List< List < size_t > > nums;
    readElem(nums, sequences);
    if (!nums.empty())
    {
      printSequences(std::cout, nums);
      std::cout << '\n';
    }

    printSums(std::cout, nums);
    std::cout << '\n';
  }

  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
