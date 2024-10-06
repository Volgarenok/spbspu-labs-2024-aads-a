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
  List< ullList > processedData = processData(sequences);
  outputSequences(sequences);
  if (isEmpty(sequences))
  {
    std::cout << "0" << "\n";
    return 0;
  }
  outputProcessedData(processedData);
  List< unsigned long long int > sums;
  try
  {
    sums = calculateSums(processedData);
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  outputSums(sums);
}
