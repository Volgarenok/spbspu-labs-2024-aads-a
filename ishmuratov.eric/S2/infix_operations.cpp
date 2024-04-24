#include "infix_operations.hpp"
#include "stack.hpp"
#include "checks.hpp"

void ishmuratov::input_infix(const std::string & line, Queue< std::string > & input_queue)
{
  std::string token;
  for (char i : line)
  {
    if (!std::isspace(i))
    {
      token += i;
    }
    else
    {
      input_queue.push(token);
      token = "";
    }
  }
  input_queue.push(token);
}

void ishmuratov::topostfix(Queue< std::string > & process_queue, Queue< std::string > & result_queue)
{
  Stack< std::string > process_stack;
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
}
