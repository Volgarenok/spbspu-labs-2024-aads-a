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
  bool overflow_detected = false;
  if (sequences.empty())
  {
    std::cout << "0" << "\n";
    return 0;
  }
  List< ullList > processedData = processData(sequences);
  List< unsigned long long int > sums = calculateSums(processedData);
  try
  {
    outputSequences(sequences);
    if (isEmpty(sequences))
    {
      std::cout << "0" << "\n";
      return 0;
    }
  }
  catch (const std::out_of_range & e)
  {
    std::cerr << e.what() << "\n";
    overflow_detected = true;
  }
  outputProcessedData(processedData);
  if (!overflow_detected)
  {
    outputSums(sums);
  }
  return overflow_detected;
}
