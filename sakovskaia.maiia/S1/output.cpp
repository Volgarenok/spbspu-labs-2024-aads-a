#include "output.hpp"
void sakovskaia::outputSequences(const List< std::pair< std::string, List< unsigned long long int > > > & sequences)
{
  for (const auto & seq : sequences)
  {
    std::cout << seq.first << " ";
  }
  std::cout << '\n';
}

void sakovskaia::outputProcessedData(const List< List< unsigned long long int > > & processedData)
{
  for (const auto & list : processedData)
  {
    for (const auto & num : list)
    {
      std::cout << num << " ";
    }
    std::cout << '\n';
  }
}

void sakovskaia::outputSums(const List< unsigned long long int > & sums)
{
  for (const auto & sum : sums)
  {
    std::cout << sum << " ";
  }
  std::cout << '\n';
}
