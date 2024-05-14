#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"
#include "readinput.hpp"
#include "outputnames.hpp"
#include "outputsequences.hpp"
#include "outputsums.hpp"

int main()
{
  petuhov::List< std::pair< std::string, petuhov::List< unsigned long long > > > sequences;

  petuhov::readInput(sequences, std::cin);

  if (sequences.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  petuhov::List< unsigned long long > sums;

  try
  {
    petuhov::outputNames(std::cout, sequences);
    petuhov::outputSequences(std::cout, sequences, sums);
    petuhov::outputSums(std::cout, sums);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
