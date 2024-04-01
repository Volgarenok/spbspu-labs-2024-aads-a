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
    std::cout << inputString << "|";
    currentQueue.push(inputString);
  }
  std::cout << currentQueue.size();
  while (!currentQueue.empty())
  {
    //std::cout << processStack.top();
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
    else if ((temp == "+") || (temp == "-"))
    {
      if (processStack.empty())
      {
        processStack.push(temp);
      }
      else
      {
        while ((!processStack.empty()) && (!highPriority(processStack.top())) && (processStack.top() != "("))
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
        while ((!processStack.empty()) && (highPriority(processStack.top()))&& (processStack.top() != "("))
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
  std::string result = "";
  while (!resultQueue.empty())
  {
    //std::cout << resultQueue.front() << "\t";
    result += resultQueue.front();
    resultQueue.pop();
  }
  std::cout << result << "\n";
  /*int res = 0;
  size_t countOperands = 0;
  std::stack< int > operandsStack;
  while (!resultQueue.empty())
  {
    if (std::isdigit(resultQueue.front()[0]))
    {
      operandsStack.push(std::stoi(resultQueue.front()));
      resultQueue.pop();
      ++countOperands;
    }
    else
    {
      if (countOperands > 1)
      {
        int num1 = operandsStack.top();
        operandsStack.pop();
        int num2 = operandsStack.top();
        operandsStack.pop();
        std::string op = resultQueue.front();
        std::cout << op;
        resultQueue.pop();
        res += calculateExpression(num1, num2, op);
      }
      else
      {
        std::cerr << "Wrong expression\n";
      }
    }
  }
  std::cout << res;*/
}