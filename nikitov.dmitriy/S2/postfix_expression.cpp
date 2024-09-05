#include "postfix_expression.hpp"
#include <limits>
#include <stack.hpp>

nikitov::PostfixExpression::PostfixExpression(const Queue< PostfixType >& postfixQueue):
  data_(postfixQueue)
{}

nikitov::PostfixExpression nikitov::PostfixExpression::operator+(long long value) const
{
  PostfixExpression newExpression(*this);
  newExpression.data_.push(nikitov::PostfixType('+'));
  newExpression.data_.push(nikitov::PostfixType(value));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator-(long long value) const
{
  PostfixExpression newExpression(*this);
  newExpression.data_.push(nikitov::PostfixType('-'));
  newExpression.data_.push(nikitov::PostfixType(value));;
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator*(long long value) const
{
  PostfixExpression newExpression(*this);
  newExpression.data_.push(nikitov::PostfixType('*'));
  newExpression.data_.push(nikitov::PostfixType(value));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator/(long long value) const
{
  PostfixExpression newExpression(*this);
  newExpression.data_.push(nikitov::PostfixType('/'));
  newExpression.data_.push(nikitov::PostfixType(value));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator%(long long value) const
{
  PostfixExpression newExpression(*this);
  newExpression.data_.push(nikitov::PostfixType('%'));
  newExpression.data_.push(nikitov::PostfixType(value));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator+(PostfixExpression value) const
{
  PostfixExpression newExpression(*this);
  while (!value.data_.empty())
  {
    newExpression.data_.push(value.data_.top());
    value.data_.pop();
  }
  newExpression.data_.push(PostfixType('+'));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator-(PostfixExpression value) const
{
  PostfixExpression newExpression(*this);
  while (!value.data_.empty())
  {
    newExpression.data_.push(value.data_.top());
    value.data_.pop();
  }
  newExpression.data_.push(PostfixType('-'));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator/(PostfixExpression value) const
{
  PostfixExpression newExpression(*this);
  while (!value.data_.empty())
  {
    newExpression.data_.push(value.data_.top());
    value.data_.pop();
  }
  newExpression.data_.push(PostfixType('/'));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator*(PostfixExpression value) const
{
  PostfixExpression newExpression(*this);
  while (!value.data_.empty())
  {
    newExpression.data_.push(value.data_.top());
    value.data_.pop();
  }
  newExpression.data_.push(PostfixType('*'));
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator%(PostfixExpression value) const
{
  PostfixExpression newExpression(*this);
  while (!value.data_.empty())
  {
    newExpression.data_.push(value.data_.top());
    value.data_.pop();
  }
  newExpression.data_.push(PostfixType('%'));
  return newExpression;
}

bool isAdditionOverflow(long long first, long long second)
{
  long long maxNum = std::numeric_limits< long long >::max();
  long long minNum = std::numeric_limits< long long >::min();
  bool isOverflow = first > 0 && maxNum - first < second;
  isOverflow = isOverflow || (first < 0 && minNum - first > second);
  return isOverflow;
}

bool isSubstractionOverflow(long long first, long long second)
{
  long long maxNum = std::numeric_limits< long long >::max();
  long long minNum = std::numeric_limits< long long >::min();
  bool isOverflow = first > 0 && minNum + first > second;
  isOverflow = isOverflow || (first < 0 && maxNum + first < second - 1);
  return isOverflow;
}

bool isMultiplicationOverflow(long long first, long long second)
{
  long long maxNum = std::numeric_limits< long long >::max();
  long long minNum = std::numeric_limits< long long >::min();
  bool isOverflow = (first > 0 && second > 0) && maxNum / first < second;
  isOverflow = isOverflow || ((first < 0 && second < 0) && maxNum / first > second);
  isOverflow = isOverflow || ((first > 0 && second < 0) && minNum / first > second);
  isOverflow = isOverflow || ((first < 0 && second > 0) && minNum / first < second);
  return isOverflow;
}

bool isDivisionOverflow(long long first, long long second)
{
  long long minNum = std::numeric_limits< long long >::min();
  return first == minNum && second == -1;
}

long long nikitov::PostfixExpression::solve()
{
  Stack< long long > solverStack;
  size_t countElem = 0;
  while (!data_.empty())
  {
    PostfixType postfixValue = data_.top();
    data_.pop();
    if (postfixValue.getType() == ExprTypeName::operation)
    {
      if (countElem >= 2)
      {
        long long second = solverStack.top();
        solverStack.pop();
        long long first = solverStack.top();
        solverStack.pop();
        long long result = 0;
        char symb = postfixValue.getOperation();
        switch (symb)
        {
        case '+':
        {
          if (isAdditionOverflow(first, second))
          {
            throw std::out_of_range("Error: Addition overflow");
          }
          result = first + second;
          break;
        }
        case '-':
        {
          if (isSubstractionOverflow(first, second))
          {
            throw std::out_of_range("Error: Subtraction overflow");
          }
          result = first - second;
          break;
        }
        case '*':
        {
          if (isMultiplicationOverflow(first, second))
          {
            throw std::out_of_range("Error: Mulptiplication overflow");
          }
          result = first * second;
          break;
        }
        case '/':
        {
          if (second == 0)
          {
            throw std::logic_error("Error: Division by zero");
          }
          if (isDivisionOverflow(first, second))
          {
            throw std::out_of_range("Error: Division overflow");
          }
          result = first / second;
          break;
        }
        case '%':
        {
          if (second == 0)
          {
            throw std::logic_error("Error: Division by zero");
          }
          result = first % second;
          if (result < 0)
          {
            result += second;
          }
          break;
        }
        default:
          throw std::logic_error("Error: Wrong operation");
          break;
        }
        solverStack.push(result);
        --countElem;
      }
      else
      {
        throw std::logic_error("Error: Wrong order of operations");
      }
    }
    else
    {
      solverStack.push(postfixValue.getOperand());
      ++countElem;
    }
  }
  long long result = solverStack.top();
  solverStack.pop();
  return result;
}
