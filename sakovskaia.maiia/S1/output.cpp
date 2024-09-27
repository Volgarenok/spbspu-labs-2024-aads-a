#include "output.hpp"
void sakovskaia::outputSequences(const List< std::pair< std::string, List< unsigned long long int > > > & sequences)
{
  for (const auto & seq : sequences)
  {
    std::cout << seq.first << " ";
    if (seq.second.empty()) {
        std::cout << "0";
    }
  }
  std::cout << '\n';
}

void sakovskaia::outputProcessedData(const List< List< unsigned long long int > > & processedData)
{
  for (const auto & list : processedData)
  {
    if (list.empty())
    {
      std::cout << "Empty List";
    }
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
