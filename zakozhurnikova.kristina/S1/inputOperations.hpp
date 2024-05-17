#ifndef INPUT_OPERATIONS_HPP
#define INPUT_OPERATIONS_HPP
#include <iosfwd>
#include <utility>
#include <list.hpp>

namespace zakozhurnikova
{
  using pair = std::pair< std::string, List< size_t > >;
  void readList(List< pair >& list, std::istream& in);
}

#endif
