#include <iostream>
#include <fstream>
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

void input_infix(std::string line, ishmuratov::Queue< std::string > & input_queue)
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

void topostfix(ishmuratov::Queue< std::string > & process_queue, ishmuratov::Queue< std::string > & result_queue)
{
  ishmuratov::Stack< std::string > process_stack;
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

void calculate_postfix(ishmuratov::Queue< std::string > & result_queue, ishmuratov::Stack< int > & operands)
{
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
}

int main(int argc, char * argv[])
{
  using namespace ishmuratov;
  std::istream * input;
  std::ifstream input_file;

  if (argc == 1)
  {
    input = &std::cin;
  }
  else if (argc == 2)
  {
    input_file.open(argv[1]);
    input = &input_file;
  }

  Stack< std::string > process_stack;
  Queue< std::string > process_queue;
  Queue< std::string > result_queue;
  Stack< int > operands;
  Stack< int > results;
  std::string line;

  while (std::getline(*input, line))
  {
    input_infix(line, process_queue);
    topostfix(process_queue, result_queue);
    calculate_postfix(result_queue, operands);
    results.push(operands.top());
  }

  std::cout << results.drop();
  while (!results.empty())
  {
    std::cout << " " << results.drop();
  }
  std::cout << "\n";

  return 0;
}
