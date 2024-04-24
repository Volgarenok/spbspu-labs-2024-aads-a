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
    if (sequences.getSize() == 0)
    {
      std::cout << "0\n";
      return 0;
    }
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
