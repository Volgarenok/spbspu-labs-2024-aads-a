#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <list.hpp>
#include "stack.hpp"

using namespace skuratov;

int operatorPrecedence(char op)
{
  if (op == '-' || op == '+')
  {
    return 1;
  }
  else if (op == '%' || op == '*' || op == '/')
  {
    return 2;
  }
  return 0;
}

int applyOperation(int a, int b, char op)
{
  if (op == '+')
  {
    return a + b;
  }
  else if (op == '-')
  {
    return a - b;
  }
  else if (op == '*')
  {
    return a * b;
  }
  else if (op == '/')
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }
    return a / b;
  }
  else if (op == '%')
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }
    return a % b;
  }
  throw std::invalid_argument("Invalid operator");
}

int evaluateExpression(const std::string& exp)
{
  std::istringstream iss(exp);
  std::string op;
  Stack< int > operands;
  Stack< char > operators;

  while (iss >> op)
  {
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
    {
      while (!operators.empty() && operatorPrecedence(operators.top()) >= operatorPrecedence(op[0]))
      {
        char op = operators.top();
        operators.drop();
        int b = operands.top();
        operands.drop();
        int a = operands.top();
        operands.drop();
        operands.push(applyOperation(a, b, op));
      }
      operators.push(op[0]);
    }
    else
    {
      operands.push(std::stoi(op));
    }
  }

  while (!operators.empty())
  {
    char op = operators.top();
    operators.drop();
    int b = operands.top();
    operands.drop();
    int a = operands.top();
    operands.drop();
    operands.push(applyOperation(a, b, op));
  }
  return operands.top();
}

int main(int argc, char* argv[])
{
  List< std::string > exp;
  std::string line;

  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    while (std::getline(infile, line))
    {
      if (!line.empty())
      {
        exp.pushBack(line);
      }
    }
  }
  else
  {
    while (std::getline(std::cin, line))
    {
      if (!line.empty())
      {
        exp.pushBack(line);
      }
    }
  }

  List< int > results;

  for (auto it = exp.cbegin(); it != exp.cend(); ++it)
  {
    try
    {
      int result = evaluateExpression(*it);
      results.pushBack(result);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
    }
  }

  for (auto it = results.cbegin(); it != results.cend(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << '\n';
  return 0;
}
