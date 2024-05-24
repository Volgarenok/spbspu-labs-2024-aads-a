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
    std::cout << '\n';

    printSequences(std::cout, sequences);
    std::cout << '\n';

    printSums(std::cout, sequences);
    std::cout << '\n';
  }

  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
