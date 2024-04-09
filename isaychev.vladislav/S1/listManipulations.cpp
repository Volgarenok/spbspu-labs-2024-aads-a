#include "listManipulations.hpp"

size_t isaychev::getElemOnPos(size_t pos, ullList & l)
{
  fwdIterator< unsigned long long int > it = l.begin();
  for (size_t i = 1; i < pos; ++i)
  {
    ++it;
  }
  return *it;
}

size_t isaychev::getMaxFwdElemNum(List< std::pair< std::string, ullList > > & list)
{
  size_t maxSize = 0;
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    size_t temp = getElemNum(i->second);
    maxSize = std::max(maxSize, temp);
  }
  return maxSize;
}

void isaychev::reverseAll(List< std::pair< std::string, ullList > > & list)
{
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    i->second.reverse();
  }
  list.reverse();
}
