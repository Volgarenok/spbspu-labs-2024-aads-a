#include "listManipulations.hpp"

void isaychev::fillIterList(pairList & list, List< fwdIterator< ulli > > & lToFill)
{
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    const fwdIterator< ulli > it = i->second.begin();
    lToFill.push_front(it);
  }
}

size_t isaychev::getMaxFwdElemNum(pairList & list)
{
  size_t maxSize = 0;
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    size_t temp = getElemNum(i->second);
    maxSize = std::max(maxSize, temp);
  }
  return maxSize;
}

void isaychev::reverseAll(pairList & list)
{
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    i->second.reverse();
  }
  list.reverse();
}
