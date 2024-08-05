#ifndef INPUTOUTPUT_HPP
#define INPUTOUTPUT_HPP

#include <cstddef>
#include <ostream>
#include <list.hpp>

namespace sivkov
{
  void outputNames(List< std::pair< std::string, List< size_t > > >& list, std::ostream& out);
  void outputSums(const List< size_t >& numbers, std::ostream& out);
  void input(std::istream& input, List< std::pair< std::string, List< size_t > > >& list);
  void outputNums(const List< std::pair< std::string, List< size_t > > >& list, List< size_t >& numbers, std::ostream& out);
}

#endif
