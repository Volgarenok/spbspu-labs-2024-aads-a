#include "outputResults.hpp"
#include <limits>
#include <stdexcept>
#include "listManipulations.hpp"

void isaychev::outputNames(std::ostream & out, pairList & list)
{
  auto i = list.begin();
  out << i->first;
  for (++i ; i != list.end(); ++i)
  {
    out << " " << i->first;
  }
  out << "\n";
}

void isaychev::outputNumbers(std::ostream & out, pairList & list)
{
  size_t upperBorder = getMaxFwdElemNum(list) + 1;
  List< size_t > nums;
  List< fwdIterator< unsigned long long int > > iters;
  fillIterList(list, iters);
  iters.reverse();

  for (size_t n = 1; n < upperBorder; ++n)
  {
    auto it = list.begin();
    for (auto j = iters.begin(); j != iters.end(); ++j)
    {
      size_t bord = getElemNum(it->second);
      ++it;
      if (n > bord)
      {
        continue;
      }
      nums.push_front(*(*j));
      ++(*j);
    }
    nums.reverse();
    outputList(out, nums);
    nums.clear();
  }
}

void isaychev::outputSums(std::ostream & out, pairList & list)
{
  size_t upperBorder = getMaxFwdElemNum(list) + 1;
  List< size_t > sums;
  unsigned long long int maxSize = std::numeric_limits< unsigned long long int >::max(), sum = 0;
  List< fwdIterator< unsigned long long int > > iters;
  fillIterList(list, iters);
  iters.reverse();

  for (size_t n = 1; n < upperBorder; ++n)
  {
    auto it = list.begin();
    for (auto j = iters.begin(); j != iters.end(); ++j)
    {
      size_t bord = getElemNum(it->second);
      ++it;
      size_t num = 0;
      if (n > bord)
      {
        continue;
      }
      num = *(*j);
      ++(*j);
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
