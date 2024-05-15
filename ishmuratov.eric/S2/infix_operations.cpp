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
    std::string temp = process_queue.back();
    process_queue.pop();
    try
    {
      std::stoll(temp);
      result_queue.push(temp);
    }
    catch (...)
    {
      if (temp == "(")
      {
        process_stack.push(temp);
      }
      else if (temp == ")")
      {
        while (!process_stack.empty() && process_stack.top() != "(")
        {
          result_queue.push(process_stack.top());
          process_stack.pop();
        }
        process_stack.pop();
      }
      else if (is_operator(temp))
      {
        if (process_stack.empty())
        {
          process_stack.push(temp);
        }
        else
        {
          while (!process_stack.empty() && (get_priority(process_stack.top()) == 2 || get_priority(temp) == 1))
          {
            if (process_stack.top() == "(")
            {
              break;
            }
            result_queue.push(process_stack.top());
            process_stack.pop();
          }
          process_stack.push(temp);
        }
      }
    }
  }
  while(!process_stack.empty())
  {
    result_queue.push(process_stack.top());
    process_stack.pop();
  }
}
