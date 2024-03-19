#include <iostream>
#include "queue.hpp"
#include "stack.hpp"

bool isOperator(const std::string& opr)
{
  return opr == "+" || opr == "-" || opr == "*" || opr == "/" || opr == "%";
}

bool high_priority(const std::string& opr)
{
  return (opr == "*" || opr == "/" || opr == "%");
}

bool low_priority(const std::string& opr)
{
  return (high_priority(opr) || (opr == "+") || (opr == "-"));
}

int calculate(int n1, int n2, const std::string& opr)
{
  if (opr == "+")
  {
    return n1 + n2;
  }
  else if (opr == "-")
  {
    return n1 - n2;
  }
  else if (opr == "*")
  {
    return n1 * n2;
  }
  else if (opr == "/")
  {
    return n1 / n2;
  }
  else if (opr == "%")
  {
    return n1 % n2;
  }
  return 0;
}

int main()
{
  using namespace ishmuratov;
  Stack< std::string > process_stack;
  Queue< std::string > process_queue;
  Queue< std::string > result_queue;
  Stack< int > operands;

  std::string input;
  std::cin >> input;
  while (!std::cin.eof())
  {
    process_queue.push(input);
    std::cin >> input;
  }

  while (!process_queue.empty())
  {
    std::string temp = process_queue.drop();
    if (std::isdigit(temp[0]))
    {
      result_queue.push(temp);
    }
    else if (temp == "(")
    {
      process_stack.push(temp);
    }
    else if (temp == ")")
    {
      while (process_stack.top() != "(")
      {
        result_queue.push(process_stack.drop());
      }
      process_stack.drop();
    }
    else if ((temp == "+") || (temp == "-"))
    {
      if (process_stack.empty())
      {
        process_stack.push(temp);
      }
      else
      {
        while (!process_stack.empty() && low_priority(process_stack.top()))
        {
          result_queue.push(process_stack.drop());
        }
        process_stack.push(temp);
      }
    }
    else if (temp == "*" || temp == "/" || temp == "%")
    {
      if (process_stack.empty())
      {
        process_stack.push(temp);
      }
      else
      {
        while (!process_stack.empty() && high_priority(process_stack.top()))
        {
          result_queue.push(process_stack.drop());
        }
        process_stack.push(temp);
      }
    }
  }
  while(!process_stack.empty())
  {
    result_queue.push(process_stack.drop());
  }

  while (!result_queue.empty())
  {
    std::string temp = result_queue.drop();
    if (isdigit(temp[0]))
    {
      operands.push(std::stoi(temp));
    }
    else if (isOperator(temp))
    {
      int n2 = operands.drop();
      int n1 = operands.drop();
      int res = calculate(n1, n2, temp);
      operands.push(res);
    }
  }

  std::cout << operands.top();
  return 0;
}
