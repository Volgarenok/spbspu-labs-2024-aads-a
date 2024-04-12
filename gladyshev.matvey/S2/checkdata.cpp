#include "checkdata.hpp"

bool gladyshev::isNumber(const std::string& s)
{
  try
  {
    std::stoull(s);
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool gladyshev::isOperator(const std::string& s)
{
  return s ==  "-" || s == "+" || s == "*" || s == "/" || s == "%";
}

bool gladyshev::checkQuality(const std::string& top, const std::string& now)
{
  return top == "*" || top == "%" || top == "*" || now == "+" || now == "-";
}
