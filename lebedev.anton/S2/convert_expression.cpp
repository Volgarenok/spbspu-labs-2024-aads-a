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

static bool checkOperationPriority(lebedev::InfixExpression a, lebedev::Operation b)
{
  if (a.getType() == lebedev::Symbol::operation)
  {
    return getOperationPriority(a.getOperation()) >= getOperationPriority(b.operation);
  }
  else
  {
    return false;
  }
}

lebedev::Queue< lebedev::PostfixExpression > lebedev::convertExpression(Queue< InfixExpression > & queue_infix)
{
  Stack< InfixExpression > stack;
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
      bool stack_primary_op = !stack.empty() && checkOperationPriority(stack.top(), curr_symbol.getOperation());
      while (stack_primary_op)
      {
        queue_postfix.push(PostfixExpression(stack.top().getOperation()));
        stack.pop();
        stack_primary_op = !stack.empty() && checkOperationPriority(stack.top(), curr_symbol.getOperation());
      }
      stack.push(curr_symbol);
    }
    else if (curr_symbol.getType() == Symbol::bracket)
    {
      if (curr_symbol.isOpenBracket())
      {
        stack.push(curr_symbol);
      }
      else
      {
        while (!stack.empty() && stack.top().getType() != Symbol::bracket)
        {
          queue_postfix.push(PostfixExpression(stack.top().getOperation()));
          stack.pop();
        }
        if (stack.empty())
        {
          throw std::invalid_argument("ERROR: Invalid bracket");
        }
        else
        {
          stack.pop();
        }
      }
    }
  }
  while (!stack.empty())
  {
    if (stack.top().getType() == Symbol::operation)
    {
      queue_postfix.push(PostfixExpression(stack.top().getOperation()));
      stack.pop();
    }
    else
    {
      throw std::invalid_argument("ERROR: Invalid symbol");
    }
  }
  return queue_postfix;
}
