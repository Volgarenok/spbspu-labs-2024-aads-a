#include "sum_func.hpp"
#include <stdexcept>
#include <limits>

namestnikov::SumFunc::SumFunc():
  result_(0),
  line_("")
{}

int namestnikov::SumFunc::getResult() const
{
  return result_;
}

std::string namestnikov::SumFunc::getLine() const
{
  return line_;
}

void namestnikov::SumFunc::operator()(const std::pair< const int, std::string > & data)
{
  constexpr int maxNum = std::numeric_limits< int >::max();
  constexpr int minNum = std::numeric_limits< int >::min();
  bool isOverflow = (result_ > 0) && (maxNum - result_ < data.first);
  isOverflow = isOverflow || ((result_ < 0) && (data.first < 0) && (minNum - result_ > data.first));
  if (isOverflow)
  {
    throw std::overflow_error("Overflow error");
  }
  result_ += data.first;
  line_ += " " + data.second;
}
