#ifndef CALCULATE_EXPRESSION_HPP
#define CALCULATE_EXPRESSION_HPP

#include "queue.hpp"
#include "tokens.hpp"

namespace novokhatskiy
{
  long long calculatePostExp(Queue< Postfix >&& inQueue);
  long long Addition(const long long& op1, const long long& op2);
  long long Substraction(const long long& op1, const long long& op2);
  long long Multiplication(const long long& op1, const long long& op2);
  long long Division(const long long& op1, const long long& op2);
  long long Mod(const long long& op1, const long long& op2);
}

#endif
