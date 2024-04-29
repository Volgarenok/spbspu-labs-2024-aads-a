#ifndef SAFE_MATH_FUNCTIONS_HPP
#define SAFE_MATH_FUNCTIONS_HPP

#include <cstddef>
#include <limits>

namespace grechishnikov
{
  const long long int MAX = std::numeric_limits< long long int >::max();
  const long long int MIN = std::numeric_limits< long long int >::min();

  long long int addTwo(long long int first, long long int second);
  long long int subtractTwo(long long int first, long long int second);
  long long int multiplyTwo(long long int first, long long int second);
  long long int divideTwo(long long int first, long long int second);
  long long int modTwo(long long int first, long long int second);
}

#endif
