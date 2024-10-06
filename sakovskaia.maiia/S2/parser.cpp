#include "parser.hpp"

namespace sakovskaia
{
  int precedence(const std::string & op)
  {
    if (op == "+" || op == "-")
    {
      return 1;
    }
    if (op == "*" || op == "/" || op == "%")
    {
      return 2;
    }
    return 0;
  }

  Queue< std::string > infix_to_postfix(const std::string & expression)
  {
    std::istringstream iss(expression);
    std::string token;
    Queue< std::string > output;
    Stack< std::string > operators;
    while (iss >> token)
    {
      if (isOperand(token))
      {
        output.push(std::move(token));
      }
      else if (isOperator(token))
      {
        while (!operators.empty() && isOperator(operators.front()) &&
        precedence(operators.front()) >= precedence(token))
        {
          output.push(operators.pop());
        }
        operators.push(std::move(token));
      }
      else if (token == "(")
      {
        operators.push(std::move(token));
      }
      else if (token == ")")
      {
        while (!operators.empty() && operators.front() != "(")
        {
          output.push(operators.pop());
        }
        if (operators.empty())
        {
          throw std::runtime_error("Mismatched parentheses");
        }
        operators.pop();
      }
      else
      {
        throw std::runtime_error("Invalid token: " + token);
      }
    }
    while (!operators.empty())
    {
      std::string op = operators.pop();
      if (op == "(" || op == ")")
      {
        throw std::runtime_error("Mismatched parentheses");
      }
      output.push(std::move(op));
    }
    return output;
  }

  int evaluate_postfix(const Queue< std::string > & postfix)
  {
    Stack< int > operands;
    Queue< std::string > postfix_copy = postfix;
    while (!postfix_copy.empty())
    {
      std::string token = postfix_copy.pop();
      if (isOperand(token))
      {
        try
        {
          int value = std::stoi(token);
          operands.push(value);
        }
        catch (const std::invalid_argument&)
        {
          throw std::runtime_error("Invalid operand: " + token);
        }
      }
      else if (isOperator(token))
      {
        if (operands.empty())
        {
          throw std::runtime_error("Insufficient operands for operator: " + token);
        }
        int rhs = operands.pop();
        if (operands.empty())
        {
          throw std::runtime_error("Insufficient operands for operator: " + token);
        }
        int lhs = operands.pop();
        if (token == "+")
        {
          operands.push(lhs + rhs);
        }
        else if (token == "-")
        {
          operands.push(lhs - rhs);
        }
        else if (token == "*")
        {
          operands.push(lhs * rhs);
        }
        else if (token == "/")
        {
          if (rhs == 0)
          {
            throw std::runtime_error("Division by zero");
          }
          operands.push(lhs / rhs);
        }
        else if (token == "%")
        {
          if (rhs == 0)
          {
            throw std::runtime_error("Modulo by zero");
          }
          operands.push(lhs % rhs);
        }
        else
        {
          throw std::runtime_error("Unknown operator: " + token);
        }
      }
      else
      {
        throw std::runtime_error("Invalid token in postfix expression: " + token);
      }
    }
    if (operands.empty())
    {
      throw std::runtime_error("No operands in expression");
    }
    int result = operands.pop();
    if (!operands.empty())
    {
      throw std::runtime_error("Too many operands in expression");
    }
    return result;
  }
}
