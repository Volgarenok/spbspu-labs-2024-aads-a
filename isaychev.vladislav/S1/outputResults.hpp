#ifndef OUTPUTRESULTS_HPP
#define OUTPUTRESULTS_HPP

#include <string>
#include <iosfwd>
#include "list.hpp"

namespace isaychev
{
  using ullList = List< unsigned long long int >;
  void outputResults(std::ostream & out, List< std::pair< std::string, ullList > > & list);
  void outputNames(std::ostream & out, List< std::pair< std::string, ullList > > & list);
  void outputNumbers(std::ostream & out, List< std::pair< std::string, ullList > > & list);
  void outputSums(std::ostream & out, List< std::pair< std::string, ullList > > & list);
}

#endif
