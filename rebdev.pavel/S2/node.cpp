#include "node.hpp"

#include <stdexcept>
#include <limits>

rebdev::node::node(long long number) noexcept:
  number_(number),
  operationPriority_(0)
{}

rebdev::node::node(char operationName):
  operationName_(operationName),
  operationPriority_(0)
{
  if ((operationName == '+') || (operationName == '-'))
  {
    operationPriority_ = 1;
  }
  else if ((operationName == '/') || (operationName == '*') || (operationName == '%'))
  {
    operationPriority_ = 2;
  }
  else if ((operationName == '(') || (operationName == ')'))
  {
    operationPriority_ = 3;
  }
  else
  {
    throw std::logic_error("unknown type of operation");
  }
}

bool rebdev::node::operator>=(const node & origNode) const noexcept
{
  return (operationPriority_ >= origNode.operationPriority_);
}
bool rebdev::node::operator!=(char sym) const noexcept
{
  return (operationName_ != sym);
}

long long rebdev::node::getResult() const
{
  return number_;
}
long long rebdev::node::getResult(long long first, long long second) const
{
  long long llMax = std::numeric_limits< long long >::max();
  long long llMin = std::numeric_limits< long long >::min();

  long long result = 0;
  bool upOverflow = false, lowOverflow = false;
  switch (operationName_)
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

      result = first / second;
      break;

    case '%':
      result = first % second;
      break;

    default:
      throw std::logic_error("uncorrect type of operation!");
  }
  return result;
}

long long rebdev::node::getPriority() const noexcept
{
  return operationPriority_;
}

bool rebdev::node::isSignSame(long long f, long long s) const noexcept
{
  return (((f > 0) && (s > 0)) || ((f < 0) && (s < 0)));
}
