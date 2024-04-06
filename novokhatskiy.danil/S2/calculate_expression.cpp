#include "calculate_expression.hpp"
#include <stdexcept>
#include <limits>
#include "stack.hpp"

long long novokhatskiy::calculateExp(long long& val1, long long& val2, char oper)
{
  long long result = {};
  switch (oper)
  {
  case '+':
  {
    long long maxSize = std::numeric_limits< long long >::max();
    if (maxSize - val1 < val2)
    {
      throw std::out_of_range("Sum overflow");
    }
    result = val1 + val2;
    break;
  }
  case '-':
  {
    long long minSize = std::numeric_limits< long long >::min();
    if (minSize + val1 > val2)
    {
      throw std::out_of_range("Subtraction overflow");
    }
    result = val1 - val2;
    break;
  }
  case '*':
  {
    long long maxSize = std::numeric_limits< long long >::max();
    if (maxSize / val1 < val1)
    {
      std::out_of_range("Multiplication overflow");
    }
    result = val1 * val2;
    break;
  }
  case '/':
  {
    if (val2 == 0)
    {
      throw std::logic_error("Dividing by zero");
    }
    long long minSize = std::numeric_limits< long long >::min();
    if (val1 == minSize && val2 == -1)
    {
      throw std::out_of_range("Dividing overflow");
    }
    result = val1 / val2;
  }
  case '%':
  {
    result = val1 % val2;
    if (result < 0)
    {
      result += val2;
    }
    break;
  }
  default:
    throw std::invalid_argument("Can't calculate the expression because of the operation");
    break;
  }
  return result;
}

long long novokhatskiy::calculatePostExp(Queue<novokhatskiy::Postfix>& postQ)
{
  long long result = {};
  Stack< long long> curr;
  size_t countOperands = {};
  while (!postQ.empty())
  {
    if (postQ.front().type == PartsOfExpression::OPERAND)
    {
      curr.push(postQ.data_.back().data.operand.value);
      postQ.drop();
      countOperands++;
    }
    if (countOperands >= 2)
    {
      char op = postQ.data_.back().data.operation.operation;
      postQ.drop();
      long long num1 = curr.drop();
      long long num2 = curr.drop();
      result = calculateExp(num1, num2, op);
      countOperands = 0;
    }
  }
  return result;
}
