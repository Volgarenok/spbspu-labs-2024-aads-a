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
    if (sequences.getSize() == 0)
    {
      std::cout << "0\n";
      return 0;
    }
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
