#include "outputData.hpp"

#include <limits>
#include <stdexcept>

#include <list/binList.hpp>

using BinList_t = arakelyan::BinList< std::pair< std::string, arakelyan::BinList< size_t > > >;

void arakelyan::outputPairsNames(std::ostream &out, BinList_t listOfPairs)
{
  for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
  {
    if (iter != listOfPairs.begin())
    {
      out << " ";
    }
    out << iter->first;
  }
}

void arakelyan::outputPairsLists(std::ostream &out, BinList_t &listOfPairs, arakelyan::BinList< size_t > &sumList)
{
  if ((listOfPairs.get_size() != 1) && !(listOfPairs.begin()->second.empty()))
  {
    out << "\n";
  }

  size_t maxSize = std::numeric_limits< size_t >::max();
  bool overflow = false;

  for (size_t i = 0; i < listOfPairs.get_size(); ++i)
  {
    size_t outed = 0;
    size_t sum = 0;
    for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
    {
      if (!iter->second.empty())
      {
        if (outed != 0)
        {
          out << " ";
        }
        out << iter->second.front();
        ++outed;
        if (sum < (maxSize - iter->second.empty()))
        {
          sum += iter->second.front();
        }
        else
        {
          overflow = true;
        }
        iter->second.pop_front();
      }
    }
    sumList.push_back(sum);
    out << "\n";
  }
  if (overflow)
  {
    throw std::overflow_error("overflow error!");
  }
}

void arakelyan::outputPairListsSums(std::ostream &out, arakelyan::BinList< size_t > sumList)
{
  for (auto it = sumList.begin(); it != sumList.end(); ++it)
  {
    if (it != sumList.begin())
    {
      out << " ";
    }
    out << *it;
  }
}
