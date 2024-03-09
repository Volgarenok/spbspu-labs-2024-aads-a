#include "outputData.hpp"
#include "binList.cpp"
#include "binList.hpp"
#include <stdexcept>

void arakelyan::outputPairsNames(arakelyan::BinList< std::pair< std::string, arakelyan::BinList< size_t > > > listOfPairs, std::ostream & out)
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


void arakelyan::outputPairsLists(arakelyan::BinList< std::pair< std::string, arakelyan::BinList< size_t > > > &listOfPairs, arakelyan::BinList< size_t > &sumList, std::ostream & out)
{
  if ((listOfPairs.getSize() != 1) && !(listOfPairs.begin()->second.isEmpty()))
  {
    out << "\n";
  }

  size_t maxSize = std::numeric_limits< size_t >::max();
  bool overflow = false;

  //elements
  for (size_t i = 0; i < listOfPairs.getSize(); ++i)
  {
    size_t outed = 0;
    size_t sum = 0;
    for (auto iter = listOfPairs.begin(); iter != listOfPairs.end(); ++iter)
    {
      if (!iter->second.isEmpty())
      {
        if (outed == 0)
        {
          out << "";
        }
        else {
          out << " ";
        }
        out << iter->second.getFirst();
        ++outed;
        if (sum < (maxSize - iter->second.isEmpty()))
        {
          sum += iter->second.getFirst();
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


void arakelyan::outputPairListsSums(arakelyan::BinList< size_t > sumList, std::ostream & out)
{

  for (auto it = sumList.begin(); it != sumList.end(); ++it)
  {
    if (it != sumList.begin())
    {
      out << " ";
    }
    out << *it;
  }
  out << "\n";
}
