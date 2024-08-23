#include "summator.hpp"
#include <limits>
#include <stdexcept>

baranov::Summator::Summator():
  resultKey_(0),
  resultValue_()
{}

void baranov::Summator::operator()(const std::pair< int, std::string > & data)
{
  resultKey_ = sum(resultKey_, data.first);
  resultValue_ += ' ' + data.second;
}

int baranov::Summator::getResultKey() const
{
  return resultKey_;
}

std::string baranov::Summator::getResultValue() const
{
  return resultValue_;
}

int baranov::Summator::sign(int value)
{
  return (value > 0) ? 1: ((value < 0) ? -1: 0);
}

bool baranov::Summator::same_sign(int a, int b)
{
  return sign(a) * sign(b) > 0;
}

int baranov::Summator::sum(int a, int b)
{
  const int max_int = std::numeric_limits< int >::max();
  const int min_int = std::numeric_limits< int >::min();
  if (same_sign(a, b) && (a > 0))
  {
    if (max_int - a >= b)
    {
      return a + b;
    }
  }
  else if (same_sign(a, b) && (a < 0))
  {
    if (min_int - a <= b)
    {
      return a + b;
    }
  }
  else if (!same_sign(a, b))
  {
    return a + b;
  }
  throw std::overflow_error("Overflow");
}

