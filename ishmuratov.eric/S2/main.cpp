#include <iostream>
#include <fstream>
#include <limits>
#include <exception>
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

void input_infix(const std::string & line, ishmuratov::Queue< std::string > & input_queue)
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

void calculate_postfix(ishmuratov::Queue< std::string > & result_queue, ishmuratov::Stack< long long int > & operands)
{
  while (!result_queue.empty())
  {
    std::string temp = result_queue.drop();
    if (isdigit(temp[0]))
    {
      operands.push(std::stoll(temp));
    }
    else if (isOperator(temp))
    {
      long long int n2 = operands.drop();
      long long int n1 = operands.drop();
      long long int res = 0;
      long long int max_value = std::numeric_limits< long long int >::max();
      long long int min_value = std::numeric_limits< long long int >::min();

      if (temp == "+")
      {
        if (n1 > max_value - n2)
        {
          throw std::overflow_error("Sum overflow!");
        }
        res = n1 + n2;
      }
      else if (temp == "-")
      {
        if (n1 < min_value + n2)
        {
          throw std::underflow_error("Subtraction underflow!");
        }
        res = n1 - n2;
      }
      else if (temp == "*")
      {
        if (n1 > max_value / n2)
        {
          throw std::overflow_error("Multiplication overflow!");
        }
        else if (n1 < min_value / n2)
        {
          throw std::underflow_error("Multiplication underflow!");
        }
        res = n1 * n2;
      }
      else if (temp == "/")
      {
        if (n2 == 0)
        {
          throw std::logic_error("Division by 0!");
        }
        res = n1 / n2;
      }
      else if (temp == "%")
      {
        if (n2 == 0)
        {
          throw std::logic_error("Division by 0!");
        }
        res = n1 % n2;
        if (res < 0)
        {
          res += n2;
        }
      }
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
  else
  {
    std::cerr << "Too many arguments!\n";
    return 1;
  }

  Stack< std::string > process_stack;
  Queue< std::string > process_queue;
  Queue< std::string > result_queue;
  Stack< long long int > operands;
  Stack< long long int > results;
  std::string line;

  try
  {
    while (std::getline(*input, line))
    {
      if (!line.empty())
      {
        input_infix(line, process_queue);
        topostfix(process_queue, result_queue);
        calculate_postfix(result_queue, operands);
        results.push(operands.top());
      }
    }
  }
  catch (std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!results.empty())
  {
    std::cout << results.drop();
    while (!results.empty())
    {
      std::cout << " " << results.drop();
    }
    std::cout << "\n";
  }
  return 0;
}