#include "getSum.hpp"

void zakozhurnikova::KeySum::operator()(int data)
{
  long long maxNum = std::numeric_limits< long long >::max();
  long long minNum = std::numeric_limits< long long >::min();
  if ((result_ > 0 && maxNum - result_ < data) || (result_ < 0 && data < 0 && minNum - result_ > data))
  {
    throw std::overflow_error("Error: Addition overflow");
  }
  result_ += data;
}
