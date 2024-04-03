#include "infixFunction.hpp"
#include <iostream>

void rebdev::pushOperation(stack< node > & operationStack, queue< node > & postfixQueue, char operation)
{
  if  (operation == ')')
  {
    while (operationStack.top() != '(')
    {
      postfixQueue.push(operationStack.top());
      operationStack.pop();
    }
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
      while (!(newNode >= operationStack.top()))
      {
        postfixQueue.push(operationStack.top());
        operationStack.pop();
      }
    }
    operationStack.push(newNode);
  }
}
