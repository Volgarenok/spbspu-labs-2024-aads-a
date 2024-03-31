#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "stack.hpp"

int main()
{
  std::queue<std::string> prefixExpression;
  std::queue<std::string> postfixExpression;
  std::stack<std::string> operationStack;
  std::string inString = "";
  while (std::cin >> inString)
  {
    if (std::isdigit(inString[0]))
    {
      postfixExpression.push(inString);      
    }
    else
    {
      if (!operationStack.empty())
      {
        postfixExpression.push(operationStack.top());
        operationStack.pop();
      }
      operationStack.push(inString);
    }
  }
}
