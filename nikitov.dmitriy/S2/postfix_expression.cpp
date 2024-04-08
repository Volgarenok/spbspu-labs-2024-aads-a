#include "postfix_expression.hpp"
#include <limits>
#include "stack.hpp"

void inputOperator(nikitov::PostfixExpression& expression, char symb, long long value)
{
  expression.add(nikitov::PostfixType(symb));
  expression.add(nikitov::PostfixType(value));
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator+(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '+', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator-(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '-', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator*(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '*', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator/(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '/', value);
  return newExpression;
}

nikitov::PostfixExpression nikitov::PostfixExpression::operator%(long long value) const
{
  PostfixExpression newExpression(*this);
  inputOperator(newExpression, '%', value);
  return newExpression;
}

void nikitov::PostfixExpression::add(PostfixType& value)
{
  data.push(value);
}

void nikitov::PostfixExpression::add(PostfixType&& value)
{
  data.push(std::move(value));
}

nikitov::PostfixType nikitov::PostfixExpression::remove()
{
  return data.drop();
}

size_t nikitov::PostfixExpression::size() const
{
  return data.size();
}

bool nikitov::PostfixExpression::empty() const
{
  return data.empty();
}

long long nikitov::PostfixExpression::solve()
{
  Stack< long long > solverStack;
  size_t countElem = 0;
  while (!data.empty())
  {
    PostfixType postfixValue = data.drop();
    if (postfixValue.getType() == ExprTypeName::operation)
    {
      if (countElem >= 2)
      {
        long long maxNum = std::numeric_limits< long long >::max();
        long long minNum = std::numeric_limits< long long >::min();
        long long second = solverStack.drop();
        long long first = solverStack.drop();
        long long result = 0;
        char symb = postfixValue.getOperation();
        switch (symb)
        {
        case '+':
        {
          if ((first > 0 && maxNum - first < second) || (first < 0 && minNum - first > second))
          {
            throw std::out_of_range("Error: Addition overflow");
          }
          result = first + second;
          break;
        }
        case '-':
        {
          if ((first > 0 && minNum + first > second) || (first < 0 && maxNum + first < second - 1))
          {
            throw std::out_of_range("Error: Subtraction overflow");
          }
          result = first - second;
          break;
        }
        case '*':
        {
          if (((first > 0 && second > 0) && maxNum / first < second) ||
            ((first < 0 && second < 0) && maxNum / first > second) ||
            ((first > 0 && second < 0) && minNum / first > second) ||
            ((first < 0 && second > 0) && minNum / first < second))
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
          if (first == minNum && second == -1)
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
  return solverStack.drop();
}
