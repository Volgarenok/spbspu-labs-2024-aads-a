#include "detectSym.hpp"
#include <string>
#include <cstddef>
#include <stdexcept>
#include <cstring>
#include <climits>

namespace spiridonov
{
  bool isNumber(const std::string& s)
  {
    if (s.empty())
    {
      return false;
    }

    for (char ch : s)
    {
      if (!isdigit(ch))
      {
        return false;
      }
    }

    return true;
  }

  bool isOp(const std::string& s)
  {
    if (s.size() != 1)
    {
      return false;
    }

    char ch = s.front();

    return ch == '*' || ch == '-' || ch == '/' || ch == '%' || ch == '+';
  }

  size_t evalPriority(char op)
  {
    size_t priority = 0;
    switch (op)
    {
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '+':
    case '-':
      priority = 1;
      break;
    case '(':
      priority = 3;
      break;
    default:
      throw std::runtime_error("Invalid operator");
    };
    return priority;
  }

  bool priorityEqualOrGreater(char op1, char op2)
  {
    return evalPriority(op1) >= evalPriority(op2);
  }

  bool isLeftBracket(const std::string& s)
  {
    if (s.size() != 1)
    {
      return false;
    }

    char ch = s.front();

    return ch == '(';
  }

  bool isRightBracket(const std::string& s)
  {
    if (s.size() != 1)
    {
      return false;
    }

    char ch = s.front();

    return ch == ')';
  }

  int opPlus(int a, int b)
  {
    if (b < 0 && a < INT_MIN - b)
    {
      throw std::runtime_error("Bad operand");
    }

    if (a > 0 && b > INT_MAX - a)
    {
      throw std::runtime_error("Bad operand");
    }

    return a + b;
  }

  int opMinus(int a, int b)
  {
    return opPlus(a, -b);
  }

  int opMultiply(int a, int b)
  {
    if (a > INT_MAX / b || a < INT_MIN / b)
    {
      throw std::runtime_error("Bad operand");
    }

    return a * b;
  }

  int opDiv(int a, int b)
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }

    return a / b;
  }

  int opMod(int a, int b)
  {
    if (b == 0)
    {
      throw std::runtime_error("Modulo by zero");
    }

    return ((a % b) + b) % b;
  }

}
