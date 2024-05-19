#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <limits>
#include <list.hpp>
#include "stack.hpp"
#include "queue.hpp"

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

long long int applyOperation(long long int a, long long int b, char op)
{
  constexpr long long int minValue = std::numeric_limits< long long int >::min();
  constexpr long long int maxValue = std::numeric_limits< long long int >::max();

  if (op == '+')
  {
    if (a > maxValue - b)
    {
      throw std::overflow_error("Invalid addition");
    }
    return a + b;
  }
  else if (op == '-')
  {
    if (a < minValue + b)
    {
      throw std::overflow_error("Invalid subtraction");
    }
    return a - b;
  }
  else if (op == '*')
  {
    if (a > maxValue / b || a < minValue / b)
    {
      throw std::overflow_error("Invalid multiplication");
    }
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

std::string infixToPostfix(const std::string& exp)
{
  std::istringstream iss(exp);
  std::string postfixExp;
  Stack< char > operators;

  std::string op;
  while (iss >> op)
  {
    if (op == "(")
    {
      operators.push('(');
    }
    else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
    {
      while (!operators.empty() && operators.top() != '(' && operatorPrecedence(operators.top()) >= operatorPrecedence(op[0]))
      {
        postfixExp += operators.top();
        postfixExp += ' ';
        operators.drop();
      }
      operators.push(op[0]);
    }
    else if (op == ")")
    {
      while (!operators.empty() && operators.top() != '(')
      {
        postfixExp += operators.top();
        postfixExp += ' ';
        operators.drop();
      }
      if (!operators.empty() && operators.top() == '(')
      {
        operators.drop();
      }
    }
    else
    {
      postfixExp += op;
      postfixExp += ' ';
    }
  }

  while (!operators.empty())
  {
    postfixExp += operators.top();
    postfixExp += ' ';
    operators.drop();
  }
  return postfixExp;
}

void evaluatePostfixExpression(const std::string& exp, Queue< long long int >& resultQueue)
{
  std::istringstream iss(exp);
  Stack< long long int > operands;

  std::string op;
  while (iss >> op)
  {
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
    {
      long long int b = operands.top();
      operands.drop();
      long long int a = operands.top();
      operands.drop();
      operands.push(applyOperation(a, b, op[0]));
    }
    else
    {
      operands.push(std::stoll(op));
    }
  }
  resultQueue.push(operands.top());
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

  List< Queue< long long int > > results;

  for (auto it = exp.cbegin(); it != exp.cend(); ++it)
  {
    try
    {
      std::string postfixExp = infixToPostfix(*it);
      Queue< long long int > resultQueue;
      evaluatePostfixExpression(postfixExp, resultQueue);
      results.pushBack(resultQueue);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << '\n';
      return 1;
    }
  }

  for (auto it = results.cbegin(); it != results.cend(); ++it)
  {
    Queue< long long int > resultQueue = *it;
    while (!resultQueue.empty())
    {
      std::cout << resultQueue.front() << " ";
      resultQueue.drop();
    }
  }
  std::cout << '\n';
  return 0;
}
