#include <limits>
#include <stdexcept>

#include "keySum.hpp"

belokurskaya::KeySum::KeySum():
  resultKey_(0),
  resultValue_()
{}

void belokurskaya::KeySum::operator()(const std::pair< const int, std::string >& data)
{
  resultKey_ = sum(resultKey_, data.first);
  resultValue_ += data.second;
}

std::pair< int, std::string > belokurskaya::KeySum::getResult() const
{
  return std::make_pair(resultKey_, resultValue_);
}

int belokurskaya::KeySum::getResultKey() const
{
  return resultKey_;
}

std::string belokurskaya::KeySum::getResultValue() const
{
  return resultValue_;
}

bool belokurskaya::KeySum::sameSign(int a, int b)
{
  return (a > 0 && b > 0) || (a < 0 && b < 0);
}

int belokurskaya::KeySum::sum(int a, int b)
{
  const int max = std::numeric_limits< int >::max();
  const int min = std::numeric_limits< int >::min();
  if (sameSign(a, b))
  {
    if ((a > 0 && a > max - b) || (a < 0 && a < min - b))
    {
      throw std::overflow_error("Overflow");
    }
  }
  return a + b;
}
