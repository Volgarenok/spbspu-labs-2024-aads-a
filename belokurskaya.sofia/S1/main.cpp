#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "SequenceVector.hpp"
#include "readSequences.hpp"

int main()
{
  using namespace belokurskaya;
  try
  {
    SequenceVector sequences = readSequences();

    if (sequences.getSize() == 0)
    {
      std::cout << "0\n";
      throw std::runtime_error("No sequences provided.");
    }

    for (size_t i = 0; i < sequences.getSize(); ++i)
    {
      std::cout << sequences[i].getName() << " ";
    }
    std::cout << "\n";

    size_t maxLength = 0;
    for (size_t i = 0; i < sequences.getSize(); ++i)
    {
      maxLength = std::max(maxLength, sequences[i].getSequence().size());
    }

    for (size_t j = 0; j < maxLength; ++j)
    {
      for (size_t i = 0; i < sequences.getSize(); ++i)
      {
        const List< int >& seq = sequences[i].getSequence();
        if (j < seq.size())
        {
          std::cout << seq.at(j) << " ";
        }
      }
    }
    std::cout << "\n";

    for (size_t i = 0; i < sequences.getSize(); ++i)
    {
      const List< int >& seq = sequences[i].getSequence();
      int sum = 0;
      for (size_t j = 0; j < seq.size(); ++j)
      {
        sum += seq.at(j);
      }
      std::cout << sum << " ";
    }
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
