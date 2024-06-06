#include "calculatePostfix.hpp"
#include "stack.hpp"

long long int baranov::calculatePostfix(Queue< Token > & exp)
{
  Stack< Token > stack;
  while (!exp.empty())
  {
    Token t = exp.front();
    exp.pop();
    if (t.type == TokenType::OPERAND)
    {
      stack.push(t);
    }
    else if (t.type == TokenType::OPERATION)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("Invalit postfix expression");
      }
      long long int a = stack.top().value.operand.value;
      stack.pop();
      long long int b = stack.top().value.operand.value;
      long long int result = 0;

      switch (t.value.operation.type)
      {
        case OperationType::ADDITION:
          result = b + a;
          break;
        case OperationType::SUBTRACTION:
          result = b - a;
          break;
        case OperationType::MULTIPLICATION:
          result = b * a;
          break;
        case OperationType::DIVISION:
          result = b / a;
          break;
      }
      stack.top().value.operand.value = result;
    }
    else
    {
      throw std::logic_error("Invalid postfix expression");
    }
  }
  if (stack.size() != 1 || stack.top().type != TokenType::OPERAND)
  {
    throw std::logic_error("Invalid postfix expression");
  }
  return stack.top().value.operand.value;
}

