#include "operators.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

long long zaitsev::safePlus(long long a, long long b)
{
  if (a >= 0 && std::numeric_limits< long long >::max() - a < b)
  {
    throw std::runtime_error("Sum overflow");
  }
  if (a < 0 && std::numeric_limits< long long >::lowest() - a > b)
  {
    throw std::runtime_error("Sum underflow");
  }
  return a + b;
}

long long zaitsev::safeMinus(long long a, long long b)
{
  if (b < 0 && std::numeric_limits< long long >::max() + b < a)
  {
    throw std::runtime_error("Difference overflow");
  }
  if (b >= 0 && std::numeric_limits< long long >::lowest() + b > a)
  {
    throw std::runtime_error("Difference underflow");
  }
  return a - b;
}

long long zaitsev::safeDiv(long long a, long long b)
{
  if (b == 0 || (b < 0 && a < 0 && a == std::numeric_limits< long long >::lowest() && b == -1))
  {
    throw std::runtime_error("Division overflow");
  }
  return a / b;
}

long long zaitsev::safeMod(long long a, long long b)
{
  if (b == 0 || (a == std::numeric_limits< long long >::lowest() && b == -1))
  {
    throw std::runtime_error("Mod overflow");
  }
  return (a % b >= 0) ? a % b : a % b + b;
}

long long zaitsev::safeMult(long long a, long long b)
{
  if (a == 0 || b == 0)
    return 0;
  if ((a * b) / b != a)
  {
    throw std::runtime_error("Multiplication overflow");
  }
  return a * b;
}