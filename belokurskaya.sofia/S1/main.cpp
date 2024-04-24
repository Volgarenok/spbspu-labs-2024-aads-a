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
    SequenceVector sequences = readSequences();
    printNames(sequences);
    printSequences(sequences);
    printSums(sequences);
  }

  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
