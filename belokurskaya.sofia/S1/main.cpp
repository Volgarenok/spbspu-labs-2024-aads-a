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

    printNames(std::cout, sequences);

    printSequences(std::cout, sequences);
    printSums(std::cout, sequences);
  }

  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
