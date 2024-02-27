#include "output_list.hpp"
#include <fstream>
#include <limits>
#include "iterator.hpp"

void nikitov::outputList(List< std::pair< std::string, List< size_t > > >& pairsList, std::ostream& output)
{
  if (pairsList.size() == 0)
  {
    throw std::invalid_argument("Error: Empty list");
  }

  ListIterator< std::pair< std::string, List< size_t > > > pairsIterator = pairsList.begin();
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

  bool isOverflow = false;
  size_t sizeOfPairs = pairsList.size();
  size_t* sums = new size_t[sizeOfPairs]{};
  for (size_t i = 0; i != maxSize; ++i)
  {
    size_t sum = 0;
    pairsIterator = pairsList.begin();
    for (size_t j = 0; j != sizeOfPairs; ++j)
    {
      ListIterator< size_t > numbersIterator = pairsIterator->second.begin();
      if (i < pairsIterator->second.size())
      {
        size_t number = *(numbersIterator.advance(i));
        if (sum != 0)
        {
          output << ' ';
        }
        output << number;

        size_t maxNum = std::numeric_limits< size_t >::max();
        if (maxNum - number < sum)
        {
          isOverflow = true;
        }
        else
        {
          sum += number;
        }
      }
      ++pairsIterator;
    }
    sums[i] = sum;
    output << '\n';
  }

  if (isOverflow)
  {
    delete[] sums;
    throw std::out_of_range("Error: Sum is out of range");
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

