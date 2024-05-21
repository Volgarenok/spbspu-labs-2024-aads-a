#include "complement_functor.hpp"
#include <string>
#include <limits>
#include <stdexcept>

erohin::ComplementFunctor erohin::ComplementFunctor::operator()(const std::pair< int, std::string > & pair)
{
  if (sum > 0 && pair.first > std::numeric_limits< int >::max() - sum)
  {
    throw std::overflow_error("Overflow of number");
  }
  else if (sum < 0 && pair.first < 0 && pair.first < std::numeric_limits< int >::min() - sum)
  {
    throw std::underflow_error("Underflow of number");
  }
  sum += pair.first;
  names += (' ' + pair.second);
  return *this;
}
