#ifndef RANDOMGENERATORS_HPP
#define RANDOMGENERATORS_HPP

#include <deque>
#include <cstddef>

namespace zhalilov
{
  void fillRandomInts(std::deque< int > &, size_t);
  void fillRandomFloats(std::deque< float > &, size_t);
}

#endif
