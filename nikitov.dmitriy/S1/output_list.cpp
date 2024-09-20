#include "output_list.hpp"
#include <ostream>
#include <limits>
#include <list.hpp>

void nikitov::outputSequenceNames(const listOfPairs& pairsList, size_t& maxSize, std::ostream& output)
{
  for (auto pairsIterator = pairsList.cbegin(); pairsIterator != pairsList.cend(); ++pairsIterator)
  {
    maxSize = std::max(maxSize, pairsIterator->second.size());
    if (pairsIterator != pairsList.cbegin())
    {
      output << ' ';
    }
    output << pairsIterator->first;
  }
}

bool nikitov::outputSequences(const listOfPairs& pairsList, List< size_t >& sumsList, size_t maxSize, std::ostream& output)
{
  bool isOverflow = false;
  for (size_t i = 0; i != maxSize; ++i)
  {
    size_t sum = 0;
    bool isFirst = true;
    for (auto pairsIterator = pairsList.cbegin(); pairsIterator != pairsList.cend(); ++pairsIterator)
    {
      auto numbersIterator = pairsIterator->second.cbegin();
      if (i < pairsIterator->second.size())
      {
        std::advance(numbersIterator, i);
        size_t number = *numbersIterator;
        if (isFirst)
        {
          isFirst = false;
        }
        else
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
    if (!isFirst)
    {
      output << '\n';
    }
    sumsList.push_back(sum);
  }
  return isOverflow;
}

void nikitov::outputSums(const List< size_t >& sumsList, std::ostream& output)
{
  for (auto sumsIterator = sumsList.cbegin(); sumsIterator != sumsList.cend(); ++sumsIterator)
  {
    if (sumsIterator != sumsList.cbegin())
    {
      output << ' ';
    }
    output << *sumsIterator;
  }
}

