#include "sum_keys.hpp"
#include <limits>
#include <stdexcept>

nikitov::SumKeys::SumKeys():
  key_(0),
  line_()
{}

void nikitov::SumKeys::operator()(const std::pair< int, std::string >& value)
{
  constexpr int maxNum = std::numeric_limits< int >::max();
  constexpr int minNum = std::numeric_limits< int >::min();
  if ((key_ > 0 && maxNum - key_ < value.first) || (key_ < 0 && value.first < 0 && minNum - key_ > value.first))
  {
    throw std::overflow_error("Error: numeric overflow");
  }
  key_ += value.first;
  line_ += ' ' + value.second;
}

int nikitov::SumKeys::getKey() const
{
  return key_;
}

std::string nikitov::SumKeys::getLine() const
{
  return line_;
}
