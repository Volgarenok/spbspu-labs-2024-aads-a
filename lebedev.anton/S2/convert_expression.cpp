#include "convert_expression.hpp"
#include "stack.hpp"

static short getOperationPriority(lebedev::Operation op)
{
  if (op.operation == '+' || op.operation == '-')
  {
    return 1;
  }
  else if (op.operation == '*' || op.operation == '/' || op.operation == '%')
  {
    return 2;
  }
  else
  {
    throw std::invalid_argument("ERROR: Invalid operation");
  }
}

static bool checkOperationPriority(lebedev::Operation a, lebedev::Operation b)
{
  return getOperationPriority(a.operation) >= getOperationPriority(b.operation);
}

lebedev::Queue< lebedev::PostfixExpression > lebedev::convertExpression(Queue< InfixExpression > & queue_infix)
{
  Stack< InfixExpression > stack_processing;
  Queue< PostfixExpression > queue_postfix;

  while (!queue_infix.empty())
  {
    InfixExpression curr_symbol = queue_infix.front();
    queue_infix.pop();
    if (curr_symbol.getType() == Symbol::operand)
    {
      queue_postfix.push(PostfixExpression(curr_symbol.getOperand()));
    }
    else if (curr_symbol.getType() == Symbol::operation)
    {
      while (stack_processing.top().getType() == Symbol::operation && checkOperationPriority(stack_processing.top().getOperation(), curr_symbol.getOperation()) && !stack_processing.empty())
      {
        queue_postfix.push(PostfixExpression(curr_symbol.getOperation()));
        stack_processing.pop();
      }
      stack_processing.push(curr_symbol);
    }
    else if (curr_symbol.getType() == Symbol::bracket)
    {
      if (curr_symbol.isOpenBracket())
      {
        stack_processing.push(curr_symbol);
      }
      else
      {
        while (!stack_processing.empty() && stack_processing.top().getType() != Symbol::bracket)
        {
          queue_postfix.push(PostfixExpression(stack_processing.top().getOperation()));
          stack_processing.pop();
        }
        if (stack_processing.empty())
        {
          throw std::invalid_argument("ERROR: Invalid bracket");
        }
        else
        {
          stack_processing.pop();
        }
      }
    }
  }
  while (!stack_processing.empty())
  {
    InfixExpression curr_symbol = stack_processing.top();
    stack_processing.pop();
    if (curr_symbol.getType() == Symbol::operation)
    {
      queue_postfix.push(PostfixExpression(stack_processing.top().getOperation()));
      stack_processing.pop();
    }
    else
    {
      throw std::invalid_argument("ERROR: Invalid symbol");
    }
  }
  return queue_postfix;
}
