#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "list.hpp"
#include "readSequences.hpp"
#include "resultsPrinter.hpp"

int main()
{
  using namespace belokurskaya;
  try
  {
    List< SequencePair > sequences = readSequences(std::cin);

    printNames(sequences, std::cout);
    printSequences(sequences, std::cout);
    printSums(sequences, std::cout);
  }

  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
