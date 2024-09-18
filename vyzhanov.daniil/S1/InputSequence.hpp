#ifndef INPUTSEQUENCE_HPP
#define INPUTSEQUENCE_HPP

#include <iosfwd>
#include <utility>
#include "List.hpp"

namespace vyzhanov
{
  using pair = std::pair< std::string, List< size_t > >;
  void inputSequence(List< pair >&, std::istream&);
}

#endif
