#include "convert_to_postfix.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include "stack.hpp"
#include "data_types.hpp"


int getPrecedence(char op)
{
  if ((op == '/') || (op == '*'))
  {
    return 2;
  }
  else if ((op == '+') || (op == '-') || (op == '%'))
  {
    return 1;
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
}

bool hasHigherPriority(char op1, char op2)
{
  return (((getPrecedence(op1) == 2) && getPrecedence(op2) == 2) || getPrecedence(op2) == 1);
}

void namestnikov::convertToPostfix(Queue< namestnikov::Key > & currentQueue, Queue< namestnikov::Key > & resultQueue)
{
  Stack< namestnikov::Key > processStack;
  while (!currentQueue.empty())
  {
    namestnikov::Key temp = currentQueue.front();
    currentQueue.pop();
    if (temp.type == namestnikov::PartType::OPERAND)
    {
      resultQueue.push(temp);
    }
    else if (temp.type == namestnikov::PartType::OPEN_BRACKET)
    {
      processStack.push(temp);
    }
    else if (temp.type == namestnikov::PartType::CLOSE_BRACKET)
    {
      while (!processStack.empty() && processStack.top().type != namestnikov::PartType::OPEN_BRACKET)
      {
        namestnikov::Key temp = processStack.top();
        resultQueue.push(temp);
        processStack.pop();
      }
      if (processStack.empty())
      {
        throw std::runtime_error("Wrong brackets");
      }
      processStack.pop();
    }
    else if (temp.type == namestnikov::PartType::OPERATION)
    {
      while ((!processStack.empty()) && (processStack.top().type != namestnikov::PartType::OPEN_BRACKET))
      {
        resultQueue.push(processStack.top());
        processStack.pop();
      }
      processStack.push(temp);
    }
  }
  while (!processStack.empty())
  {
    resultQueue.push(processStack.top());
    processStack.pop();
  }
}
