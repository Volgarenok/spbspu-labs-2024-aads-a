#include "getSum.hpp"
#include <stdexcept>

void zakozhurnikova::KeySum::operator()(int data)
{
  int maxNum = std::numeric_limits< int >::max();
  int minNum = std::numeric_limits< int >::min();
  if ((result_ > 0 && maxNum - result_ < data) || (result_ < 0 && data < 0 && minNum - result_ > data))
  {
    throw std::overflow_error("Error: Addition overflow");
  }
  result_ += data;
}
