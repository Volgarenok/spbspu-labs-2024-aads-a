#include "SumStruct.hpp"
#include <stdexcept>
#include <limits>

novokhatskiy::KeySum::KeySum():
  value_(0),
  name_()
{}

bool isOverFlow(int val1, int val2)
{
  constexpr int max = std::numeric_limits< int >::max();
  constexpr int min = std::numeric_limits< int >::min();
  return (max - val1 < val2 && val1 > 0) || (val1 < 0 && val2 < 0 && min - val1 > val2);
}

void novokhatskiy::KeySum::operator()(const std::pair< int, std::string>& value)
{
  if (isOverFlow(value_, value.first))
  {
    throw std::overflow_error("Overflow");
  }
  value_ += value.first;
  name_ += ' ' + value.second;
}

int novokhatskiy::KeySum::getKey() const
{
  return value_;
}

std::string novokhatskiy::KeySum::getStr() const
{
  return name_;
}
