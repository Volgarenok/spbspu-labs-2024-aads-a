#include "complement_functor.hpp"
#include <string>
#include <limits>
#include <stdexcept>

erohin::ComplementFunctor erohin::ComplementFunctor::operator()(const std::pair< int, std::string > & pair)
{
  if (pair.first > 0 && sum > std::numeric_limits< int >::max() - pair.first)
  {
    throw std::overflow_error("Overflow of number");
  }
  else if (pair.first < 0 && sum < std::numeric_limits< int >::min() - pair.first)
  {
    throw std::underflow_error("Underflow of number");
  }

  sum += pair.first;
  names += (' ' + pair.second);
  return *this;
}
