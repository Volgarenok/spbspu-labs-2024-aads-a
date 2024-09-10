#ifndef OUTPUTRESULTS_HPP
#define OUTPUTRESULTS_HPP

#include <string>
#include <iostream>
#include <list/list.hpp>

namespace isaychev
{
  using ull = unsigned long long int;
  using ullList = List< unsigned long long int >;
  using pairList = List< std::pair< std::string, ullList > >;
  void outputNames(std::ostream & out, pairList & list);
  void outputNumbers(std::ostream & out, pairList & list);
  void outputSums(std::ostream & out, pairList & list);

  template < typename T >
  void outputList(std::ostream & out, List< T > & list)
  {
    if (!list.empty())
    {
      auto k = list.begin();
      out << *k;
      for (++k; k != list.end(); ++k)
      {
        out << " " << *k;
      }
      out << "\n";
    }
  }
}

#endif
