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
    postfixQueue.push(operationStack.top());
    operationStack.pop();
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
      }
    }
    operationStack.push(newNode);
  }
}
