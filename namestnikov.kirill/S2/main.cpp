#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "stack.hpp"

bool highPriority(std::string op)
{
  return ((op == "*") || (op == "/") || (op == "%"));
}

int calculateExpression(int num1, int num2, std::string op)
{
  if (op == "+")
  {
    return num1 + num2;
  }
  else if (op == "-")
  {
    return num1 - num2;
  }
  else if (op == "*")
  {
    return num1 * num2;
  }
  else if (op == "/")
  {
    return num1 / num2;
  }
  else if (op == "%")
  {
    return num1 % num2;
  }
  return 0;
}

int main()
{
  /*std::queue<std::string> prefixExpression;
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
  }*/
  std::stack< std::string > processStack;
  std::queue< std::string > currentQueue;
  std::queue< std::string > resultQueue;
  std::string inputString = "";
  while ((!std::cin.eof()) && (std::cin >> inputString))
  {
    currentQueue.push(inputString);
  }
  while (!currentQueue.empty())
  {
    std::string temp = currentQueue.front();
    currentQueue.pop();
    if (std::isdigit(temp[0]))
    {
      resultQueue.push(temp);
    }
    else if (temp[0] == '(')
    {
      processStack.push(temp);
    }
    else if (temp[0] == ')')
    {
      while (processStack.top() != "(")
      {
        resultQueue.push(processStack.top());
        processStack.pop();
      }
      processStack.pop();
    }
    else if ((temp == "+") || (temp == "-"))
    {
      if (processStack.empty())
      {
        processStack.push(temp);
      }
      else
      {
        while ((!processStack.empty()) && (!highPriority(processStack.top())))
        {
          resultQueue.push(processStack.top());
          processStack.pop();
        }
        processStack.push(temp);
      }
    }
    else if ((temp == "*") || (temp == "/") || (temp == "%"))
    {
      if (processStack.empty())
      {
        processStack.push(temp);
      }
      else
      {
        while ((!processStack.empty()) && (highPriority(processStack.top())))
        {
          resultQueue.push(processStack.top());
          processStack.pop();
        }
        processStack.push(temp);
      }
    }
  }
  while (!processStack.empty())
  {
    resultQueue.push(processStack.top());
    processStack.pop();
  }
  std::cout << resultQueue.size();
}