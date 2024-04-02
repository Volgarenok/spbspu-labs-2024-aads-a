#include "convert_to_postfix.hpp"
#include <queue>
#include <stack>

bool highPriority(std::string op)
{
  return ((op == "*") || (op == "/") || (op == "%"));
}

void namestnikov::convertToPostfix(std::queue< std::string > & currentQueue, std::queue< std::string > & resultQueue)
{
  std::stack< std::string > processStack;
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
}