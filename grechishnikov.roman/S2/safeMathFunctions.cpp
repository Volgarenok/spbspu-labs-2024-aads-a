#include "safeMathFunctions.hpp"
#include <stdexcept>

namespace grechishnikov
{
  constexpr long long int MAX = std::numeric_limits< long long int >::max();
  constexpr long long int MIN = std::numeric_limits< long long int >::min();
}

long long int grechishnikov::addTwo(long long int first, long long int second)
{
  if (second > 0 && MAX - second < first)
  {
    throw std::overflow_error("Addition caused an overflow");
  }
  if (second < 0 && MIN - second < first)
  {
    throw std::overflow_error("Addition caused an underflow");
  }
  return first + second;
}

long long int grechishnikov::subtractTwo(long long int first, long long int second)
{
  if (second > 0 && MIN + second > first)
  {
    throw std::overflow_error("Subtraction caused an underflow");
  }
  if (second < 0 && MAX + second < first)
  {
    throw std::overflow_error("Subtraction caused an overflow");
  }
  return first - second;
}

long long int grechishnikov::multiplyTwo(long long int first, long long int second)
{
  if (first > 0 && second > 0 && MAX / second < first)
  {
    throw std::overflow_error("Multiplication caused an overflow");
  }
  if (first < 0 && second < 0 && MAX / second > first)
  {
    throw std::overflow_error("Multiplication caused an overflow");
  }
  if (first > 0 && second < 0 && MIN / second < first)
  {
    throw std::overflow_error("Multiplication caused an underflow");
  }
  if (first < 0 && second > 0 && MIN / second > first)
  {
    throw std::overflow_error("Multiplication caused an underflow");
  }
  return first * second;
}

long long int grechishnikov::divideTwo(long long int first, long long int second)
{
  if (second == 0)
  {
    throw std::logic_error("Division by zero");
  }
  if (first == MIN && second == -1)
  {
    throw std::overflow_error("Division caused an overflow");
  }
  return first / second;
}

long long int grechishnikov::modTwo(long long int first, long long int second)
{
  if (second == 0)
  {
    throw std::logic_error("Division by zero");
  }
  long long int res = first % second;
  if (res < 0)
  {
    res += second;
  }
  return res;
}
