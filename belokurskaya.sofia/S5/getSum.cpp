#include <limits>
#include <stdexcept>

#include "getSum.hpp"

belokurskaya::KeySum::KeySum():
  resultKey_(0),
  resultValue_()
{}

void belokurskaya::KeySum::operator()(const std::pair< const int, std::string >& data)
{
  resultKey_ = sum(resultKey_, data.first);
  resultValue_ += data.second;
}

std::pair< long long int, std::string > belokurskaya::KeySum::getResult() const
{
  return std::make_pair(resultKey_, resultValue_);
}

bool belokurskaya::KeySum::sameSign(long long int a, long long int b)
{
  return (a > 0 && b > 0) || (a < 0 && b < 0);
}

long long int belokurskaya::KeySum::sum(long long int a, long long int b)
{
  const long long int max = std::numeric_limits< long long int >::max();
  const long long int min = std::numeric_limits< long long int >::min();
  if (sameSign(a, b))
  {
    if ((a > 0 && a > max - b) || (a < 0 && a < min - b))
    {
      throw std::overflow_error("Overflow");
    }
  }
  return a + b;
}
