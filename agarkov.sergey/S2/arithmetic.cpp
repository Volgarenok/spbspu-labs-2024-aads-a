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

long long agarkov::subtract(long long a, long long b)
{
  if ((b > 0) && (MIN + b > a))
  {
    throw std::overflow_error("Subtraction overflow");
  }
  return a - b;
}

