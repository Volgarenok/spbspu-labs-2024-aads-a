#include <iostream>
#include <cmath>
#include "inputList.hpp"

template < typename T >
isaychev::fwdIterator< T > getToPos(isaychev::List< T > & list, size_t pos)
{
  isaychev::fwdIterator< T > it = list.begin();
  for (size_t i = 0; i < pos; ++i)
  {
    try
    {
      ++it;
    }
    catch (const std::out_of_range &)
    {
      break;
    }
  }
  return it;
}

template < typename T >
size_t getElemNum(const isaychev::List < T > & list)
{
  size_t num = 0;
  for (auto i = list.begin(); i != list.end(); i++)
  {
    num++;
  }
//  std::cout << num << "\n";
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

  mainList.reverse();

  auto i = mainList.begin();
  std::cout << i->first;
  for (++i ; i != mainList.end(); ++i)
  {
    std::cout << " " << i->first;
  }
  std::cout << "\n";

  size_t upperBorder = getMaxFwdElemNum(mainList);
//  for (size_t n = 0; n < upperBorder; ++n)
 // {
//      for (auto j = mainList.begin(); j != mainList.end(); ++i)
//      {
        for (auto k = mainList.front().second.begin(); k != getToPos(mainList.front().second, 1); ++k)
        {
          std::cout << *k << "\n";
        }
//     }
 // }
//  std::cout <<
//auto k = 
}
