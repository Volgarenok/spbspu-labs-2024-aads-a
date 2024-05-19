#include "summator.hpp"

#include <limits>
#include <stdexcept>

void zhalilov::Summator::operator()(const std::pair < int, std::string > pair)
{
  long long max = std::numeric_limits < long long >::max();
  long long min = std::numeric_limits < long long >::min();
  if (result_ > 0 && max - result_ < pair.first)
  {
    throw std::overflow_error("addition overflow");
  }
  if (result_ < 0 && min + result_ > pair.first)
  {
    throw std::underflow_error("addition underflow");
  }
  result_ += pair.first;
  values_ += ' ' + pair.second;
}
