#include "summator.hpp"

#include <limits>
#include <stdexcept>

void zhalilov::Summator::operator()(const std::pair< int, std::string > pair)
{
  int max = std::numeric_limits< int >::max();
  int min = std::numeric_limits< int >::min();
  if (result_ > 0 && max - result_ < pair.first)
  {
    throw std::overflow_error("addition overflow");
  }
  if (result_ < 0 && pair.first < 0 && min - result_ > pair.first)
  {
    throw std::underflow_error("addition underflow");
  }
  result_ += pair.first;
  values_ += ' ' + pair.second;
}
