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
    if (((b > 0) && (a > maxValue - b)) || ((b < 0) && (a < minValue - b)))
    {
      throw std::overflow_error("Invalid addition");
    }
    return a + b;
  }
  else if (op == '-')
  {
    if (((b < 0) && (a > maxValue + b)) || ((b > 0) && (a < minValue + b)))
    {
      throw std::overflow_error("Invalid subtraction");
    }
    return a - b;
  }
  else if (op == '*')
  {
    if (a != 0 && (b > maxValue / a || b < minValue / a))
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
    long long int res = a % b;
    if (res < 0)
    {
      res += std::abs(b);
    }
    return res;
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
      if (operands.size() < 2)
      {
        throw std::runtime_error("Not enough operands for operation");
      }

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
  if (operands.size() != 1)
  {
    throw std::runtime_error("Invalid postfix expression");
  }
  resultQueue.push(operands.top());
}

void printReverse(const Queue< long long int >& queue)
{
  Queue< long long int > temp = queue;
  Stack< long long int > stack;

  while (!temp.empty())
  {
    stack.push(temp.front());
    temp.drop();
  }

  while (!stack.empty())
  {
    std::cout << stack.top() << ' ';
    stack.drop();
  }
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

  List< long long int > finalResults;
  for (auto it = results.cbegin(); it != results.cend(); ++it)
  {
    if (!it->empty())
    {
      finalResults.pushBack(it->front());
    }
  }

  Stack< long long int > reverseStack;
  for (auto it = finalResults.cbegin(); it != finalResults.cend(); ++it)
  {
    reverseStack.push(*it);
  }

  while (!reverseStack.empty())
  {
    std::cout << reverseStack.top() << ' ';
    reverseStack.drop();
  }
  std::cout << '\n';
  return 0;
}
