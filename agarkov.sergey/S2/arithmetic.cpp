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

long long agarkov::multiply(long long a, long long b)
{
  if ((a > 0) && ((MAX / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if ((a < 0) && ((MAX / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if ((a > 0) && ((MIN / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if ((a < 0) && ((MIN / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  return a * b;
}

long long agarkov::division(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("Division by 0");
  }
  return a / b;
}

long long agarkov::remaind(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("Remaind by 0");
  }
  if (a < 0)
  {
    return b + a % b;
  }
  return a % b;
}

