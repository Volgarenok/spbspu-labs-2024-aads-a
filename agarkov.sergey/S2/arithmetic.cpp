#include "arithmetic.hpp"
#include <stdexcept>
#include <limits>

namespace
{
  constexpr long long MAX = std::numeric_limits< long long >::max();
  constexpr long long MIN = std::numeric_limits< long long >::min();
}

long long agarkov::sum(long long a, long long b)
{
  if (MAX - a < b)
  {
    throw std::overflow_error("Sum overflow");
  }
  return a + b;
}

