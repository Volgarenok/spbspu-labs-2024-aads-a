#include "checkdata.hpp"

bool gladyshev::isOperator(const std::string& op)
{
  return op ==  "-" || op == "+" || op == "*" || op == "/" || op == "%";
}

bool gladyshev::checkQuality(const std::string& top, const std::string& now)
{
  return (top == "*" || top == "%" || top == "*" || now == "+" || now == "-") && (top != "(");
}
