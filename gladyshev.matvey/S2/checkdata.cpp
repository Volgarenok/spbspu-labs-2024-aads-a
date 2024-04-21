#include "checkdata.hpp"

bool gladyshev::isOperator(const std::string& s)
{
  return s ==  "-" || s == "+" || s == "*" || s == "/" || s == "%";
}

bool gladyshev::checkQuality(const std::string& top, const std::string& now)
{
  return (top == "*" || top == "%" || top == "*" || now == "+" || now == "-") && (top != "(");
}
