#ifndef OUTPUTRESULTS_HPP
#define OUTPUTRESULTS_HPP

#include <string>
#include <iosfwd>
#include "list.hpp"

namespace isaychev
{
  void outputResults(std::ostream & out, List< std::pair< std::string, List< size_t > > > & list);
}

#endif
