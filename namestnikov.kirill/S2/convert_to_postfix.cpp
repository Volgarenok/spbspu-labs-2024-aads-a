#include "convert_to_postfix.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include "stack.hpp"


int getPrecedence(std::string op)
{
  if ((op == "/") || (op == "*"))
  {
    return 2;
  }
  else if ((op == "+") || (op == "-") || (op == "%"))
  {
    return 1;
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
}

bool hasHigherPriority(std::string op1, std::string op2)
{
  return ((op1 != "(") && (((getPrecedence(op1) == 2) && getPrecedence(op2) == 2) || getPrecedence(op2) == 1));
}

void namestnikov::convertToPostfix(Queue< std::string > & currentQueue, Queue< std::string > & resultQueue)
{
  Stack< std::string > processStack;
  while (!currentQueue.empty())
  {
    std::string temp = currentQueue.front();
    currentQueue.pop();
    if (std::isdigit(temp[0]))
    {
      resultQueue.push(temp);
    }
    else if (temp == "(")
    {
      processStack.push(temp);
    }
    else if (temp == ")")
    {
      while (processStack.top() != "(")
      {
        std::string temp = processStack.top();
        resultQueue.push(temp);
        processStack.pop();
      }
      processStack.pop();
    }
    else if ((temp == "+") || (temp == "-") || (temp == "*") || (temp == "/") || (temp == "%"))
    {
      while ((!processStack.empty()) && (hasHigherPriority(processStack.top(), temp)))
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
