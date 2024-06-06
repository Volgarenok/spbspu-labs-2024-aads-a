#include "SumStruct.hpp"
#include <stdexcept>
#include <limits>

novokhatskiy::KeySum::KeySum():
  value_(0)
{}

void novokhatskiy::KeySum::operator()(const std::pair< int, std::string>& value)
{
  constexpr int max = std::numeric_limits< int >::max();
  constexpr int min = std::numeric_limits< int >::min();
  if ((value_ > 0 && max - value_ < value.first) || (value_ < 0 && value.first < 0 && min - value_ > value.first))
  {
    throw std::overflow_error("Overflow");
  }
  value_ += value.first;
}

int novokhatskiy::KeySum::getKey() const
{
  return value_;
}

std::string novokhatskiy::StrSum::getStr() const
{
  return name_;
}

novokhatskiy::StrSum::StrSum():
  name_()
{}

void novokhatskiy::StrSum::operator()(const std::pair< int, std::string >& val)
{
  name_ += ' ' + val.second;
}
