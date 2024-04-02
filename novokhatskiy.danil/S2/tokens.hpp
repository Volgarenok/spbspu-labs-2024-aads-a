#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>

namespace novokhatskiy
{
  struct ExpressionType
  {
    union ExpressionValue
    {
      char symb;
      size_t num;
    }
    value;
    PartsOfExpression part;
  };
  enum class PartsOfExpression
  {
    operand = 0,
    operation = 1,
    openBracket = 2,
    closedBracket = 3
  };
}

#endif
