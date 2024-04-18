#ifndef INPUTOUTPUT_HPP
#define INPUTOUTPUT_HPP

#include <cstddef>
#include "list.hpp"

namespace sivkov
{
  void outputNames(const List< std::pair< std::string, List< size_t > > >& list);
  void outputSums(const List< size_t >& numbers);
  void input(std::istream& input, List< std::pair< std::string, List< size_t > > >& list);
  void outputNums(const List< std::pair< std::string, List< size_t > > >& list, List< size_t >& numbers);
}

#endif
