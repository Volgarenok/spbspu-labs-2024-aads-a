#include "output_list.hpp"
#include <fstream>
#include "iterator.hpp"

void nikitov::outputList(List< std::pair< std::string, List< int > > >& pairsList, std::ostream& output)
{
  ListIterator< std::pair< std::string, List< int > > > pairsIterator = pairsList.begin();
  size_t maxSize = 0;
  for (size_t i = 0; i != pairsList.size(); ++i)
  {
    if (i != 0)
    {
      output << ' ';
    }
    output << pairsIterator->first;
    maxSize = std::max(maxSize, pairsIterator->second.size());
    pairsIterator++;
  }
  output << '\n';

  size_t sizeOfPairs = pairsList.size();
  int* sums = new int[sizeOfPairs]{};
  for (size_t i = 0; i != maxSize; ++i)
  {
    int sum = 0;
    pairsIterator = pairsList.begin();
    for (size_t j = 0; j != sizeOfPairs; ++j)
    {
      ListIterator< int > numbersIterator = pairsIterator->second.begin();
      if (i < pairsIterator->second.size())
      {
        if (sum != 0)
        {
          output << ' ';
        }
        int number = *(numbersIterator.advance(i));
        sum += number;
        output << number;
      }
      ++pairsIterator;
    }
    sums[i] = sum;
    output << '\n';
  }
  for (size_t i = 0; i != sizeOfPairs; ++i)
  {
    if (i != 0)
    {
      output << ' ';
    }
    output << sums[i];
  }

  output << '\n';
  delete[] sums;
}

