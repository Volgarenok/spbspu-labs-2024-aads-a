#ifndef LISTMANIPULATIONS_HPP
#define LISTMANIPULATIONS_HPP

#include <string>
#include "list.hpp"

namespace isaychev
{
  using ullList = List< unsigned long long int >;
  size_t getElemOnPos(size_t pos, ullList & l);
  size_t getMaxFwdElemNum(List< std::pair< std::string, ullList > > & list);
  void reverseAll(List< std::pair< std::string, ullList > > & list);

  template < typename T >
  size_t getElemNum(List < T > & list)
  {
    size_t num = 0;
    for (auto i = list.begin(); i != list.end(); i++)
    {
      num++;
    }
    return num;
  }
}

#endif
