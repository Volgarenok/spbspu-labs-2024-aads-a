#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "SequenceVector.hpp"
#include "readSequences.hpp"
#include "resultsPrinter.hpp"

int main()
{
  using namespace belokurskaya;
  try
  {
    SequenceVector sequences = readSequences(std::cin);

    const SequenceVector & constSequences = sequences;
    printNames(constSequences, std::cout);
    printSequences(constSequences, std::cout);
    printSums(constSequences, std::cout);
  }

  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
