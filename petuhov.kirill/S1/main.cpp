#include <iostream>
#include <string>
#include "list.hpp"
#include "readinput.hpp"
#include "outputnames.hpp"
#include "outputsequences.hpp"
#include "outputsums.hpp"

int main()
{
  petuhov::List< std::pair< std::string, petuhov::List< size_t > > > sequences;

  std::string input;
  std::string line;

  while (std::getline(std::cin, line))
  {
    input += line + '\n';
  }

  petuhov::readInput(sequences, input);

  if (sequences.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  petuhov::List< size_t > sums;

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
