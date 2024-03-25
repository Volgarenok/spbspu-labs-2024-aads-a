#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP

#include "queue.hpp"
#include "expression_type.hpp"

namespace nikitov
{
  struct PostfixExpression
  {
    PostfixExpression operator+(long long value);
    PostfixExpression operator-(long long value);
    PostfixExpression operator/(long long value);
    PostfixExpression operator*(long long value);
    PostfixExpression operator%(long long value);

    Queue< PostfixType > data;
  };
}
#endif
