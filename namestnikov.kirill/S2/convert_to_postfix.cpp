#include "convert_to_postfix.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include "stack.hpp"
#include "data_types.hpp"

unsigned char getPrecedence(char op)
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

void namestnikov::convertToPostfix(Queue< Key > & currentQueue, Queue< Key > & resultQueue)
{
  Stack< Key > processStack;
  while (!currentQueue.empty())
  {
    Key temp = currentQueue.front();
    currentQueue.pop();
    if (temp.getType() == PartType::OPERAND)
    {
      resultQueue.push(temp);
    }
    else if (temp.getType() == PartType::OPEN_BRACKET)
    {
      processStack.push(temp);
    }
    else if (temp.getType() == PartType::CLOSE_BRACKET)
    {
      while (!processStack.empty() && processStack.top().getType() != PartType::OPEN_BRACKET)
      {
        Key temp = processStack.top();
        resultQueue.push(temp);
        processStack.pop();
      }
      if (processStack.empty())
      {
        throw std::runtime_error("Wrong brackets");
      }
      processStack.pop();
    }
    else if (temp.getType() == PartType::OPERATION)
    {
      while ((!processStack.empty()) && (processStack.top().getType() != PartType::OPEN_BRACKET) &&
       (hasHigherPriority(processStack.top().getOperation(), temp.getOperation())))
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
