#include "output_list.hpp"
#include <fstream>
#include "iterator.hpp"

void nikitov::outputList(List< std::pair< std::string, List< int >* >* >& pairsList, std::ostream& output)
{
  ListIterator< std::pair< std::string, List< int >* >* > pairsIterator = pairsList.begin();
  size_t maxSize = 0;
  for (size_t i = 0; i != pairsList.size(); ++i)
  {
    std::pair< std::string, List< int >* >* pair = *pairsIterator;
    if (i != 0)
    {
      output << ' ';
    }
    output << pair->first;
    maxSize = std::max(maxSize, pair->second->size());
    pairsIterator++;
  }
  output << '\n';

  size_t sizeOfPairs = pairsList.size();
  int* sums = new int[sizeOfPairs]{};
  for (size_t i = 0; i != maxSize; ++i)
  {
    int sum = 0;
    size_t j = 0;
    pairsIterator = pairsList.begin();
    for (j = 0; j != sizeOfPairs; ++j)
    {
      std::pair< std::string, List< int >* >* pair = *pairsIterator;
      ListIterator< int > numbersIterator = pair->second->begin();
      if (i < pair->second->size())
      {
        int number = *(numbersIterator.advance(i));
        sum += number;
        output << number;
      }
      ++pairsIterator;
    }

    sums[j] = sum;
    output << '\n';
  }
  for (size_t i = 0; i != sizeOfPairs; ++i)
  {
    output << sums[i];
  }

  output << '\n';
  delete[] sums;
}

