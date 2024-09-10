#include "infix_operations.hpp"
#include "stack.hpp"
#include "checks.hpp"

void ishmuratov::input_infix(std::istream & input, Queue< Queue< std::string > > & input_queue)
{
  std::string line;
  while (std::getline(input, line))
  {
    if (line.empty())
    {
      continue;
    }
    Queue< std::string > temp;
    std::string token;
    for (size_t i = 0; i < line.size(); ++i)
    {
      if (!std::isspace(line[i]))
      {
        token += line[i];
      }
      else
      {
        temp.push(token);
        token = "";
      }
    }
    temp.push(token);
    input_queue.push(temp);
  }
}

void ishmuratov::to_postfix(Queue< std::string > & process_queue, Queue< std::string > & result_queue)
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
  while (!process_stack.empty())
  {
    result_queue.push(process_stack.top());
    process_stack.pop();
  }
}
