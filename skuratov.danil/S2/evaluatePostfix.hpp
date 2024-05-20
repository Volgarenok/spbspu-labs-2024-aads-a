#ifndef EVALUATE_POSTFIX_HPP
#define EVALUATE_POSTFIX_HPP

#include <stdexcept>
#include <limits>
#include "queue.hpp"
#include "infixToPostfix.hpp"

namespace skuratov
{
  long long int applyOperation(long long int a, long long int b, char op);
  long long int evaluatePostfixExpression(const std::string& exp);
}

#endif
