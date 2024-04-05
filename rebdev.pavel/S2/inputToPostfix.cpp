#include "inputToPostfix.hpp"

#include <string>
#include <sstream>

void rebdev::makePostfixQueue(queue< node > & postfixQueue, std::istream & in)
{
  stack< node > operationStack;

  while (!in.eof())
  {
    std::string inputStr;
    in >> inputStr;

    std::istringstream iss(inputStr);
    long long num = 0;
    iss >> num;

    if (!iss)
    {
      pushOperation(operationStack, postfixQueue, inputStr[0]);
    }
    else
    {
      postfixQueue.push(num);
    }
  }

  while (operationStack.size() > 0)
  {
    node topNode = operationStack.top();
    operationStack.pop();

    if (topNode.getPriority() == 3)
    {
      throw std::logic_error("Error with ( or )");
    }

    postfixQueue.push(topNode);
  }
}

void rebdev::pushOperation(stack< node > & operationStack, queue< node > & postfixQueue, char operation)
{
  if  (operation == ')')
  {
    while (operationStack.top() != '(')
    {
      postfixQueue.push(operationStack.top());
      operationStack.pop();
    }
    operationStack.pop();
  }
  else if (operation == '(')
  {
    operationStack.push(node(operation));
  }
  else
  {
    node newNode(operation);
    if (operationStack.size() > 0)
    {
      while (newNode >= operationStack.top())
      {
        postfixQueue.push(operationStack.top());
        operationStack.pop();
        if (operationStack.size() == 0) break;
      }
    }
    operationStack.push(newNode);
  }
}
