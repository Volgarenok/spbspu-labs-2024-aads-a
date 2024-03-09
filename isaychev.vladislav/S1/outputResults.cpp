#include "outputResults.hpp"
#include <limits>
#include <iostream>
#include <stdexcept>

size_t getElemOnPos(size_t pos, isaychev::ullList & l)
{
  isaychev::fwdIterator< unsigned long long int > it = l.begin();
  for (size_t i = 1; i < pos; ++i)
  {
    ++it;
  }
  return *it;
}

template < typename T >
size_t getElemNum(isaychev::List < T > & list)
{
  size_t num = 0;
  for (auto i = list.begin(); i != list.end(); i++)
  {
    num++;
  }
  return num;
}

size_t getMaxFwdElemNum(isaychev::List< std::pair< std::string, isaychev::ullList > > & list)
{
  size_t maxSize = 0;
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    size_t temp = getElemNum(i->second);
    maxSize = std::max(maxSize, temp);
  }
  return maxSize;
}

void reverseAll(isaychev::List< std::pair< std::string, isaychev::ullList > > & list)
{
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    i->second.reverse();
  }
  list.reverse();
}
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

void isaychev::outputResults(std::ostream & out, List< std::pair< std::string, ullList > > & list)
{
  reverseAll(list);

  size_t upperBorder = getMaxFwdElemNum(list) + 1;
  size_t numOfPairs = getElemNum(list);
  if (upperBorder > 1)
  {
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
        if (maxSize - num < sum)
        {
          throw std::out_of_range("sum is too big");
        }
        else
        {
          sum += num;
        }
      }
      sums.push(sum);
      sum = 0;
    }

    auto i = list.begin();
    out << i->first;
    for (++i ; i != list.end(); ++i)
    {
      out << " " << i->first;
    }
    out << "\n";

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
        nums.push(iter);
      }
      nums.reverse();
/*      auto k = nums.begin();
      out << *k;
      for (++k; k != sums.end(); ++k)
      {
        out << " " << *k;
      }
      out << "\n";*/
      outputList(out, nums);
      nums.clear();
    }

    sums.reverse();
    /*auto j = sums.begin();
    out << *j;
    for (++j; j != sums.end(); ++j)
    {
      out << " " << *j;
    }
    out << "\n";*/
    outputList(out, sums);
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
