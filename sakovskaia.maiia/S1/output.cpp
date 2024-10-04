#include "output.hpp"
void sakovskaia::outputSequences(const List< std::pair< std::string, List< unsigned long long int > > > & sequences)
{
  for (auto it = sequences.begin(); it != sequences.end(); it++)
  {
    std::cout << it->first;
    auto temp_it = it;
    if (++temp_it != sequences.end())
    {
      std::cout << " ";
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
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      std::cout << * it << " ";
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
