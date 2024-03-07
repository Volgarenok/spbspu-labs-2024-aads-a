#include <iostream>
#include <cmath>
#include "inputList.hpp"

template < typename T >
isaychev::fwdIterator< T > getToPos(const isaychev::List< T > & list, size_t pos)
{
  isaychev::fwdIterator< T > it = list.begin();
  for (size_t i = 0; i < pos; ++i)
  {
    ++it;
  }
  return it;
}

size_t getElemNum(const isaychev::List < size_t > & list)
{
  size_t num = 0;
  for (auto i = list.begin(); i != list.end(); i++)
  {
    num++;
  }
  std::cout << num << "\n";
  return num;
}

size_t getMaxFwdElemNum(const isaychev::List< std::pair< std::string, isaychev::List< size_t > > > & list)
{
  size_t maxSize = 0, k = 0;
  for (auto i = list.begin(); i != list.end(); ++i)
  {
    size_t temp = getElemNum(i->second);
//    std::cout << temp << "\n";
    maxSize = std::max(maxSize, temp);
  }
  return maxSize;
}

int main()
{
  using namespace isaychev;
  using myPair = std::pair< std::string, List< size_t > >;
  List< myPair > mainList;
  inputList(std::cin, mainList);
/*  auto i = mainList.begin();
  std::cout << i->first;
  for (++i ; i != mainList.end(); ++i)
  {
    std::cout << " " << i->first;
  }
  std::cout << "\n";
//  for (
 // {
    for (auto j = mainList.begin(); j != mainList.end(); ++i)
    {
      for (auto k = j->second.begin(); k != getToPos(mainList, 1); ++k)
      {
      }
    }
 // }*/
//  size_t upBorder = getElemNum(mainList.front().second);

  mainList.reverse();
}
