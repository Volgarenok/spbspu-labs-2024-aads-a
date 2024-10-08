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

  int64_t opPlus(int64_t a, int64_t b)
  {
    if (b < 0 && a < LLONG_MIN - b)
    {
      throw std::runtime_error("Bad operand");
    }

    if (a > 0 && b > LLONG_MAX - a)
    {
      throw std::runtime_error("Bad operand");
    }

    return a + b;
  }

  int64_t opMinus(int64_t a, int64_t b)
  {
    return opPlus(a, -b);
  }

  int64_t opMultiply(int64_t a, int64_t b)
  {
    if (a > LLONG_MAX / b || a < LLONG_MIN / b)
    {
      throw std::runtime_error("Bad operand");
    }

    return a * b;
  }

  int64_t opDiv(int64_t a, int64_t b)
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }

    return a / b;
  }

  int64_t opMod(int64_t a, int64_t b)
  {
    if (b == 0)
    {
      throw std::runtime_error("Modulo by zero");
    }

    return ((a % b) + b) % b;
  }

}
