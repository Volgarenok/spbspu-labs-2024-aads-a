#include "mathOperator.hpp"

#include <limits>
#include <stdexcept>

rebdev::mathOperator::mathOperator(char type):
  operType_(type),
  priority_(0)
  {
    switch (type)
    {
      case '+':
      case '-':
        priority_ = 1;
        break;
      case '/':
      case '*':
      case '%':
        priority_ = 2;
        break;
      case '(':
        priority_ = 0;
        break;
      default:
        throw std::logic_error("uncorrect type of operation!");
    }
  }
rebdev::mathOperator::mathOperator(const mathOperator & m):
  operType_(m.operType_),
  priority_(m.priority_)
{}
rebdev::mathOperator & rebdev::mathOperator::operator=(const mathOperator & m)
{
  this->operType_ = m.operType_;
  this->priority_ = m.priority_;
  return *this;
}
long long rebdev::mathOperator::operator()(long long first, long long second)
{
  long long llMax = std::numeric_limits< long long >::max();
  long long llMin = std::numeric_limits< long long >::min();
  long long result = 0;
  bool upOverflow = false, lowOverflow = false;

  switch (operType_)
  {
    case '+':
      if ((first > 0) && (second > 0))
        upOverflow = (first > (llMax - second));
      if ((first < 0) && (second < 0))
        lowOverflow = (first < (llMin - second));

      if (upOverflow || lowOverflow)
        throw std::logic_error("overlow as a result of operation +");
      result = first + second;
      break;

    case '-':
      if ((first > 0) && (second < 0))
        upOverflow = (first > (llMax + second));
      if ((first < 0) && (second > 0))
        lowOverflow = (first < (llMin  + second));

      if (upOverflow || lowOverflow)
        throw std::logic_error("overlow as a result of operation -");
      result = first - second;
      break;

    case '*':
      if (isSignSame(first, second))
        upOverflow = (first > (llMax / second));
      else
        lowOverflow = (first < (llMin / second));

      if (upOverflow || lowOverflow)
        throw std::logic_error("overlow as a result of operation *");
      result = first * second;
      break;

    case '/':
      if (second < 0)
        lowOverflow = (first == llMin);

      if (upOverflow || lowOverflow)
        throw std::logic_error("overlow as a result of operation /");

      result = first / second;
      break;

    case '%':
      if (first >= 0) result = first % second;
      else result = second + (first % second);
      break;

    default:
      throw std::logic_error("uncorrect type of operation!");
  }
  return result;
}

unsigned int rebdev::mathOperator::priority() const noexcept
{
  return priority_;
}
bool rebdev::mathOperator::leftBracket() const noexcept
{
  return (operType_ == '(');
}
bool rebdev::mathOperator::isSignSame(long long f, long long s) const noexcept
{
  return (((f > 0) && (s > 0)) || ((f < 0) && (s < 0)));
}

