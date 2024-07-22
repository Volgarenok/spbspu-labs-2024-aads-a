#include "parser.hpp"

namespace spiridonov
{
  int64_t Parser::parseExpression(const std::string& expression)
  {
    Stack<int64_t> operands;
    Stack<char> operators;
    std::string numString;

    for (char ch : expression)
    {
      if (ch == ' ')
      {
        if (!numString.empty())
        {
          operands.push(std::stoll(numString));
          numString.clear();
        }
        continue;
      }
      else if (isNumber(std::string(1, ch)))
      {
        numString += ch;
      }
      else if (ch == '(')
      {
        operators.push(ch);
      }
      else if (ch == ')')
      {
        while (!operators.isEmpty() && operators.getTop() != '(')
        {
          applyOperation(operands, operators.getTop());
          operators.pop();
        }
        if (!operators.isEmpty() && operators.getTop() == '(')
        {
          operators.pop();
        }
        else
        {
          throw std::runtime_error("Mismatched brackets");
        }
      }
      else if (isOp(std::string(1, ch)))
      {
        if (!numString.empty())
        {
          operands.push(std::stoll(numString));
          numString.clear();
        }

        while (!operators.isEmpty() && operators.getTop() != '(' && priorityEqualOrGreater(operators.getTop(), ch))
        {
          applyOperation(operands, operators.getTop());
          operators.pop();
        }
        operators.push(ch);
      }
      else
      {
        throw std::runtime_error("Invalid character: " + std::string(1, ch));
      }
    }

    if (!numString.empty())
    {
      operands.push(std::stoll(numString));
    }

    while (!operators.isEmpty())
    {
      char op = operators.getTop();
      operators.pop();

      if (operands.getSize() < 2)
      {
        throw std::runtime_error("Invalid expression");
      }

      int64_t b = operands.getTop();
      operands.pop();
      int64_t a = operands.getTop();
      operands.pop();

      switch (op)
      {
      case '+':
        operands.push(opPlus(a, b));
        break;
      case '-':
        operands.push(opMinus(a, b));
        break;
      case '*':
        operands.push(opMultiply(a, b));
        break;
      case '/':
        operands.push(opDiv(a, b));
        break;
      case '%':
        operands.push(opMod(a, b));
        break;
      default:
        throw std::runtime_error("Invalid operator");
      }
    }

    if (operands.getSize() != 1)
    {
      throw std::runtime_error("Invalid expression, not enough operands");
    }

    return operands.getTop();
  }

  void Parser::applyOperation(Stack<int64_t>& operands, char op)
  {
    if (operands.getSize() < 2)
    {
      throw std::runtime_error("Invalid expression");
    }
    int64_t b = operands.getTop();
    operands.pop();
    int64_t a = operands.getTop();
    operands.pop();

    switch (op)
    {
    case '+':
      operands.push(opPlus(a, b));
      break;
    case '-':
      operands.push(opMinus(a, b));
      break;
    case '*':
      operands.push(opMultiply(a, b));
      break;
    case '/':
      operands.push(opDiv(a, b));
      break;
    case '%':
      operands.push(opMod(a, b));
      break;
    default:
      throw std::runtime_error("Invalid operator");
    }
  }
}
