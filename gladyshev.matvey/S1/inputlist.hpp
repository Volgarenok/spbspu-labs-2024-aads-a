#ifndef INPUTLIST_HPP
#define INPUTLIST_HPP

#include <string>
#include <istream>

#include <list.hpp>

namespace gladyshev
{
  void readSequence(std::istream& in, List< std::pair < std::string, List< size_t > > >& list);
}

#endif
