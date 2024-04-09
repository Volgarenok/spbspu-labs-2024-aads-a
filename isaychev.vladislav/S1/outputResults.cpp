#include "outputResults.hpp"
#include <limits>
#include <iostream>
#include <stdexcept>
#include "listManipulations.hpp"

template < typename T >
void outputList(std::ostream & out, isaychev::List< T > & list)
{
  auto k = list.begin();
  out << *k;
  for (++k; k != list.end(); ++k)
  {
    out << " " << *k;
  }
  out << "\n";
}

void isaychev::outputNames(std::ostream & out, List< std::pair< std::string, ullList > > & list)
{
  auto i = list.begin();
  out << i->first;
  for (++i ; i != list.end(); ++i)
  {
    out << " " << i->first;
  }
  out << "\n";
}

void isaychev::outputNumbers(std::ostream & out, List< std::pair< std::string, ullList > > & list)
{
  size_t upperBorder = getMaxFwdElemNum(list) + 1;
  List< size_t > nums;
  for (size_t n = 1; n < upperBorder; ++n)
  {
    for (auto j = list.begin(); j != list.end(); ++j)
    {
      size_t bord = getElemNum(j->second);
      size_t iter = 0;
      if (n > bord)
      {
        continue;
      }
      iter = getElemOnPos(n, j->second);
      nums.push_front(iter);
    }
    nums.reverse();
    outputList(out, nums);
    nums.clear();
  }
}

void isaychev::outputSums(std::ostream & out, List< std::pair< std::string, ullList > > & list)
{
  size_t upperBorder = getMaxFwdElemNum(list) + 1;
  List< size_t > sums;
  unsigned long long int maxSize = std::numeric_limits< unsigned long long int >::max(), sum = 0;
  for (size_t n = 1; n < upperBorder; ++n)
  {
    for (auto j = list.begin(); j != list.end(); ++j)
    {
      size_t bord = getElemNum(j->second);
      size_t num = 0;
      if (n > bord)
      {
        continue;
      }
      num = getElemOnPos(n, j->second);
      if (maxSize - num <= sum)
      {
        throw std::out_of_range("sum is too big");
      }
      else
      {
        sum += num;
      }
    }
    sums.push_front(sum);
    sum = 0;
  }
  sums.reverse();
  outputList(out, sums);
}

void isaychev::outputResults(std::ostream & out, List< std::pair< std::string, ullList > > & list)
{
  reverseAll(list);

  size_t upperBorder = getMaxFwdElemNum(list) + 1;
  size_t numOfPairs = getElemNum(list);

  if (upperBorder > 1)
  {
    outputNames(out, list);
    outputNumbers(out, list);
    outputSums(out, list);
  }
  else if (upperBorder == 1 && numOfPairs == 1)
  {
    out << list.front().first << "\n" << 0 << "\n";
  }
  else if (numOfPairs == 0)
  {
    out << 0 << "\n";
  }

  reverseAll(list);
}
