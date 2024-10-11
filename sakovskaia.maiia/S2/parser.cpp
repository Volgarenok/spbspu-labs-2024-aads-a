#include "parser.hpp"

namespace sakovskaia
{
  int get_precedence(const std::string &op)
  {
    if (op == "*" || op == "/" || op == "%")
    {
      return 2;
    }
    else if (op == "+" || op == "-")
    {
      return 1;
    }
    return 0;
  }

  Queue< std::string > infix_to_postfix(const std::string & expression)
  {
    std::istringstream iss(expression);
    std::string token;
    Stack< std::string > operators;
    Queue< std::string > output;

    while (iss >> token)
    {
      if (isOperand(token))
      {
        output.push(std::move(token));
      }
      else if (isOperator(token))
      {
        while ((!operators.empty() && isOperator(operators.top())) &&
        (get_precedence(operators.top()) >= get_precedence(token)) && (token != "("))
        {
          output.push(std::move(operators.pop()));
        }
        operators.push(std::move(token));
      }
      else if (token == "(")
      {
        operators.push(std::move(token));
      }
      else if (token == ")")
      {
        while (!operators.empty() && operators.top() != "(")
        {
          output.push(std::move(operators.pop()));
        }
        if (operators.empty())
        {
          throw std::runtime_error("Mismatched parentheses");
        }
        operators.pop();
      }
    }
    while (!operators.empty())
    {
      output.push(std::move(operators.pop()));
    }
    return output;
  }

  int evaluate_postfix(const Queue< std::string > & postfix)
  {
    Stack< int > operands;
    Queue< std::string > copy = postfix;

    while (!copy.empty())
    {
      std::string token = copy.pop();
      if (isOperand(token))
      {
        operands.push(std::stoi(token));
      }
      else if (isOperator(token))
      {
        if (operands.empty())
        {
          throw std::runtime_error("Invalid postfix expression");
        }
        int right = operands.pop();
        int left = operands.pop();
        int result;
        if (token == "+")
        {
          result = left + right;
        }
        else if (token == "-")
        {
          result = left - right;
        }
        else if (token == "*")
        {
          result = left * right;
        }
        else if (token == "/")
        {
          if (right == 0)
          {
            throw std::runtime_error("Division by zero");
          }
          result = left / right;
        }
        else if (token == "%")
        {
          if (right == 0)
          {
            throw std::runtime_error("Modulo by zero");
          }
          result = left % right;
        }
        operands.push(std::move(result));
      }
    }
    if (operands.empty())
    {
      throw std::runtime_error("Invalid postfix expression");
    }
    return operands.pop();
  }
}

