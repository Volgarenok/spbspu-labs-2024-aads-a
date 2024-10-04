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
  try
  {
    List< ullList > processedData = processData(sequences);
    List< unsigned long long int > sums = calculateSums(processedData);
    outputSequences(sequences);
    if (isEmpty(sequences))
    {
      std::cout << "0" << "\n";
      return 0;
    }
    outputProcessedData(processedData);
    outputSums(sums);
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << "Calculating sum is impossible" << e.what() << "\n";
    return 1;
  }
  return 0;
}
