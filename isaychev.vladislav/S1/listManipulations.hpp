#ifndef LISTMANIPULATIONS_HPP
#define LISTMANIPULATIONS_HPP

#include <string>
#include "list.hpp"

namespace isaychev
{
  using ullList = List< unsigned long long >;
  using pairList = List< std::pair< std::string, ullList > >;
  size_t getMaxFwdElemNum(pairList & list);
  void reverseAll(List< std::pair< std::string, ullList > > & list);

  template < typename T >
  void fillIterList(pairList & list, List< fwdIterator< T > > & lToFill)
  {
    for (auto i = list.begin(); i != list.end(); ++i)
    {
      const fwdIterator< T > it = i->second.begin();
      lToFill.push_front(it);
    }
  }

  template < typename T >
  size_t getElemNum(List < T > & list)
  {
    size_t num = 0;
    for (auto i = list.begin(); i != list.end(); ++i)
    {
      ++num;
    }
    return num;
  }
}

#endif
