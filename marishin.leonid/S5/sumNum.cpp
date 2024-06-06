#include "sumNum.hpp"

marishin::SumNum::SumNum():
  result_(0)
{}

void marishin::SumNum::operator()(int num)
{
  int maxNum = std::numeric_limits< int >::max();
  int minNum = std::numeric_limits< int >::min();
  bool isOverflow = (result_ > 0) && (maxNum - result_ < num);
  isOverflow = isOverflow || ((result_ < 0) && (num < 0) && (minNum - result_ > num));
  if (isOverflow)
  {
    throw std::overflow_error("Overflow error");
  }
  result_ += num;
}

int marishin::SumNum::getResult() const
{
  return result_;
}
