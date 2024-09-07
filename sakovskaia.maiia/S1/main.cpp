#include "data_processing.hpp"
#include "input.hpp"
#include "list.hpp"
#include "output.hpp"
#include <iostream>
int main()
{
  using namespace sakovskaia;
  List< std::pair< std::string, ullList > > sequences;
  input(std::cin, sequences);
  if (sequences.empty())
  {
    std::cout << "0" << "\n";
    return 0;
  }
  outputSequences(sequences);
  List< ullList > processedData = processData(sequences);
  outputProcessedData(processedData);
  try
  {
    List< unsigned long long int > sums = calculateSums(processedData);
    outputSums(sums);
  }
  catch (const std::overflow_error &)
  {
    std::cerr << "Calculating sum is impossible" << "\n";
    return 1;
  }
  return 0;
}
