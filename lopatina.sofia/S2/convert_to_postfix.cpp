#include "convert_to_postfix.hpp"
#include <stdexcept>
#include "stack.hpp"

bool isLowerPriority(const lopatina::InfixType & lhs, const lopatina::InfixType & rhs)
{
  int priority_lhs = 1, priority_rhs = 1;
  char symbol_lhs = lhs.getSymbol();
  char symbol_rhs = rhs.getSymbol();
  if (symbol_lhs == '+' || symbol_lhs == '-')
  {
    priority_lhs = 0;
  }
  if (symbol_rhs == '+' || symbol_rhs == '-')
  {
    priority_rhs = 0;
  }
  return priority_lhs < priority_rhs;
}

lopatina::Queue< lopatina::PostfixType > lopatina::convertToPostfix(Queue< InfixType > & queue_source)
{
  Queue< PostfixType > queue_result;
  Stack< InfixType > stack_process;

  while (!queue_source.empty())
  {
    InfixType infix_elem = queue_source.front();
    if (infix_elem.getType() == OPEN_BRACKET)
    {
      stack_process.push(infix_elem);
    }
    else if (infix_elem.getType() == OPERAND)
    {
      PostfixType postfix_elem{infix_elem.getNumber()};
      queue_result.push(postfix_elem);
    }
    else if (infix_elem.getType() == CLOSE_BRACKET)
    {
      if (stack_process.empty())
      {
        throw std::logic_error("Wrong math expression");
      }
      InfixType elem_stack = stack_process.top();
      while (elem_stack.getType() != OPEN_BRACKET)
      {
        if (stack_process.empty())
        {
          throw std::logic_error("Wrong math expression");
        }
        PostfixType postfix_elem{elem_stack.getSymbol()};
        queue_result.push(postfix_elem);
        stack_process.pop();
        elem_stack = stack_process.top();
      }
      stack_process.pop();
    }
    else if (infix_elem.getType() == OPERATION)
    {
      while (!stack_process.empty())
      {
        InfixType elem_stack = stack_process.top();
        if (elem_stack.getType() == OPERATION && !isLowerPriority(elem_stack, infix_elem))
        {
          PostfixType postfix_elem{elem_stack.getSymbol()};
          queue_result.push(postfix_elem);
          stack_process.pop();
        }
        else
        {
          break;
        }
      }
      stack_process.push(infix_elem);
    }
    queue_source.pop();
  }
  while (!stack_process.empty())
  {
    InfixType elem_stack = stack_process.top();
    if (elem_stack.getType() == OPERATION)
    {
      PostfixType postfix_elem{elem_stack.getSymbol()};
      queue_result.push(postfix_elem);
      stack_process.pop();
    }
    else
    {
      throw std::logic_error("Wrong math expression");
    }
  }
  return queue_result;
}
