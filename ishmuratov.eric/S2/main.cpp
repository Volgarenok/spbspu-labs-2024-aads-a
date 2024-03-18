#include <iostream>
#include "queue.hpp"
#include "stack.hpp"

int main()
{
  using namespace ishmuratov;
  Stack< std::string > process_stack;
  Queue< std::string > process_queue;
  Queue< std::string > result_queue;

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
    else if ((temp == "+") || (temp == "-"))
    {
      if (process_stack.empty())
      {
        process_stack.push(temp);
      } else
      {
        result_queue.push(process_stack.drop());
        process_stack.push(temp);
      }
    }
  }
  while(!process_stack.empty())
  {
    result_queue.push(process_stack.drop());
  }
  int n1 = std::stoi(result_queue.drop());
  int n2 = std::stoi(result_queue.drop());
  while (!result_queue.empty())
  {
    std::string sign = result_queue.drop();
    if (sign == "+")
    {
      n1 = n1 + n2;
    }
    else if (sign == "-")
    {
      n1 = n1 - n2;
    }
    if (!result_queue.empty())
    {
      n2 = std::stoi(result_queue.drop());
    }
  }
  std::cout << n1;
  return 0;
}
