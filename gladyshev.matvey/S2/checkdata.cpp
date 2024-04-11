#include "checkdata.hpp"

bool gladyshev::isNumber(const std::string& s)
{
  for (char c: s)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }
  return !s.empty();
}

bool gladyshev::isOperator(const std::string& s)
{
  return s ==  "-" || s == "+" || s == "*" || s == "/" || s == "%";
}
