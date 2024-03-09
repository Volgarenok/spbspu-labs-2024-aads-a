#include "outputResults.hpp"
#include <limits>
#include <iostream>
#include <stdexcept>

size_t getElemOnPos(size_t pos, isaychev::List< size_t > & l)
{
  isaychev::fwdIterator< size_t > it = l.begin();
  for (size_t i = 1; i < pos; ++i)
  {
    ++it;
  }
  return *it;
}

size_t getElemNum(const isaychev::List < size_t > & list)
{
  size_t num = 0;
  for (auto i = list.begin(); i != list.end(); i++)
  {
    num++;
  }
  return num;
}

size_t getMaxFwdElemNum(isaychev::List< std::pair< std::string, isaychev::List< size_t > > > & list)
{
  size_t maxSize = 0;
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    size_t temp = getElemNum(i->second);
    maxSize = std::max(maxSize, temp);
  }
  return maxSize;
}

void reverseAll(isaychev::List< std::pair< std::string, isaychev::List< size_t > > > & list)
{
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    i->second.reverse();
  }
  list.reverse();
}

void isaychev::outputResults(std::ostream & out, List< std::pair< std::string, List< size_t > > > & list)
{
  reverseAll(list);

  auto i = list.begin();
  out << i->first;
  for (++i ; i != list.end(); ++i)
  {
    out << " " << i->first;
  }
  out << "\n";

  size_t upperBorder = getMaxFwdElemNum(list) + 1;
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
      out << iter;
      if (n == bord)
      {
        out << "\n";
      }
      else
      {
        out << " ";
      }
    }
  }

  size_t maxSize = std::numeric_limits< size_t >::max(), sum = 0;
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
    out << sum;
    if (n == upperBorder - 1)
    {
      out << "\n";
    }
    else
    {
      out << " ";
    }
    sum = 0;
  }

  reverseAll(list);
}
