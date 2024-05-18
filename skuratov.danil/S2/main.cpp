#include <iostream>

namespace skuratov
{
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

  int main()
  {
    std::cout << "Initial commit for S2\n";
    return 0;
  }
}
