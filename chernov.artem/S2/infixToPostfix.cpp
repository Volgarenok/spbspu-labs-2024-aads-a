#include "infixToPostfix.hpp"
#include "operations.hpp"
#include "stack.hpp"
#include <string>
#include <cstddef>

void chernov::inputInfix(std::istream& in, Queue< queue >& infix_queue)
{
  std::string str = "";
  std::string detail = "";
  while (std::getline(in, str, '\n'))
  {
    queue temp;
    detail = "";
    if (!str.empty())
    {
      for (size_t j = 0; j < str.length(); j++)
      {
        if (!std::isspace(str[j]))
        {
          detail += str[j];
          if (str.length() - 1 == j)
          {
	    temp.push(detail);
          }
        }
        else if (!detail.empty())
        {
          temp.push(detail);
          detail = "";
        }
      }
      infix_queue.push(temp);
    }
  }
}

void chernov::convertToPostfix(Queue< queue >& infix_queue, Queue< queue >& postfix_queue)
{
  std::string detail = "";
  while (!infix_queue.empty())
  {
    queue infix_temp = infix_queue.back();
    infix_queue.pop();
    queue postfix_temp;
    Stack< std::string > stack;
    while (!infix_temp.empty())
    {
      detail = "";
      detail = infix_temp.back();
      infix_temp.pop();
      try
      {
        std::stoll(detail);
        postfix_temp.push(detail);
      }
      catch (...)
      {
        if (detail == "(")
        {
          stack.push(detail);
        }
        else if (detail == ")")
        {
          if (stack.empty())
          {
            throw std::invalid_argument("No opening bracket");
          }
          while (stack.top() != "(")
          {
            postfix_temp.push(stack.top());
            stack.pop();
          }
          stack.pop();
        }
        else if (isOperation(detail))
        {
          if (!stack.empty() && !isOperation(stack.top()))
          {
            stack.push(detail);
          }
          else
          {
            if (!stack.empty() && priority(stack.top(), detail))
            {
              postfix_temp.push(stack.top());
              stack.pop();
              stack.push(detail);
            }
            else
            {
              stack.push(detail);
            }
          }
        }
        else
        {
          throw std::invalid_argument("Something strange has been transmitted");
        }
      }
    }
    while (!stack.empty())
    {
      if (stack.top() == "(")
      {
        throw std::logic_error("Too many opening brackets");
      }
      postfix_temp.push(stack.top());
      stack.pop();
    }
    postfix_queue.push(postfix_temp);
  }
}
