#include "output_list.hpp"
#include <fstream>
#include <limits>
#include "list_iterator.hpp"

void nikitov::outputList(List< std::pair< std::string, List< size_t > > >& pairsList, std::ostream& output)
{
  if (pairsList.size() == 0)
  {
    throw std::invalid_argument("Error: Empty list");
  }

  ListIterator< std::pair< std::string, List< size_t > > > pairsIterator = pairsList.begin();
  size_t maxSize = 0;
  for (; pairsIterator != pairsList.end(); ++pairsIterator)
  {
    maxSize = std::max(maxSize, pairsIterator->second.size());
    if (pairsIterator != pairsList.begin())
    {
      output << ' ';
    }
    output << pairsIterator->first;
  }
  output << '\n';

  bool isOverflow = false;
  List< size_t > sumsList;
  for (size_t i = 0; i != maxSize; ++i)
  {
    size_t sum = 0;
    pairsIterator = pairsList.begin();
    for (; pairsIterator != pairsList.end(); ++pairsIterator)
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
    }
    sumsList.push_back(sum);
    output << '\n';
  }

  if (isOverflow)
  {
    throw std::out_of_range("Error: Sum is out of range");
  }

  ListIterator< size_t > sumsIterator = sumsList.begin();
  for (; sumsIterator != sumsList.end() ; ++sumsIterator)
  {
    if (sumsIterator != sumsList.begin())
    {
      output << ' ';
    }
    output << *sumsIterator;
  }
  output << '\n';
}

