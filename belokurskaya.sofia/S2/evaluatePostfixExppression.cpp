#include "evaluatePostfixExpression.hpp"

#include <cctype>
#include <limits>
#include <stdexcept>

#include <stack.hpp>

int belokurskaya::mod(long long int a, long long int b)
{
  return (a % b + b) % b;
}

bool belokurskaya::isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

void belokurskaya::safeStrCopy(char* dest, const char* src, size_t max_len)
{
  for (size_t i = 0; i < max_len - 1 && src[i] != '\0'; ++i)
  {
    dest[i] = src[i];
    dest[i + 1] = '\0';
  }
}

bool belokurskaya::safeAdd(long long int a, long long int b, long long int& result)
{
  long long int c = std::numeric_limits< long long int >::max() - b;
  long long int d = std::numeric_limits< long long int >::min() - b;
  return ((b > 0 && a <= c) || (b < 0 && a >= d)) && (result = a + b, true);
}

bool belokurskaya::willMultiplyOverflowOrUnderflow(long long int a, long long int b, char* errorType)
{
  if (a > 0)
  {
    if (b > 0)
    {
      if (a > (std::numeric_limits< long long int >::max() / b))
      {
        safeStrCopy(errorType, "Overflow", 30);
        return true;
      }
    }
    else
    {
      if (b < (std::numeric_limits< long long int >::min() / a))
      {
        safeStrCopy(errorType, "Underflow", 30);
        return true;
      }
    }
  }
  else
  {
    if (b > 0)
    {
      if (a < (std::numeric_limits< long long int >::min() / b))
      {
        safeStrCopy(errorType, "Underflow", 30);
        return true;
      }
    }
    else
    {
      if (a != 0 && b < (std::numeric_limits< long long int >::max() / a))
      {
        safeStrCopy(errorType, "Overflow", 30);
        return true;
      }
    }
  }
  return false;
}

bool belokurskaya::willSubtractUnderflow(long long int a, long long int b)
{
  long long int c = std::numeric_limits< long long int >::min() + b;
  long long int d = std::numeric_limits< long long int >::max() + b;
  return (b > 0 && a < c) || (b < 0 && a > d);
}

long long int belokurskaya::evaluatePostfixExpression(std::string expression)
{
  Stack< long long int > st;
  long long int num = 0;
  bool flag = false;
  for (char & c : expression)
  {
    if (std::isdigit(c))
    {
      num = num * 10 + (c - '0');
      flag = true;
    }
    else if (std::isspace(c))
    {
      if (flag)
      {
        st.push(num);
        flag = false;
        num = 0;
      }
    }
    else if (isOperator(c))
    {
      long long int operand2 = st.top();
      st.pop();
      long long int operand1 = st.top();
      st.pop();
      if (c == '+')
      {
        long long int result = 0;
        if (!safeAdd(operand1, operand2, result))
        {
          throw std::logic_error("Invalid addition");
        }
        st.push(result);
      }
      else if (c == '-')
      {
        char errorType[30];
        if (willSubtractUnderflow(operand1, operand2))
        {
          safeStrCopy(errorType, "Subtraction Underflow", 30);
          throw std::logic_error("Invalid substraction");
        }
        else
        {
          st.push(operand1 - operand2);
        }
      }
      else if (c == '*')
      {
        char errorType[10];
        if (willMultiplyOverflowOrUnderflow(operand1, operand2, errorType))
        {
          throw std::logic_error("Invalid multiplication");
        }
        else
        {
          st.push(operand1 * operand2);
        }
      }
      else if (c == '/')
      {
        if (operand2 == 0)
        {
          throw std::logic_error("Invalid division");
        }
        if (operand1 == std::numeric_limits< long long int >::min() && operand2 == -1)
        {
          throw std::logic_error("Invalid division");
        }
        st.push(operand1 / operand2);
      }
      else if (c == '%')
      {
        st.push(mod(operand1, operand2));
      }
    }
    else
    {
      throw std::invalid_argument("Unknown symbol in the argument");
    }
  }
  return st.top();
}
