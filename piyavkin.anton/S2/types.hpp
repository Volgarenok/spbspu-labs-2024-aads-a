#ifndef TYPES_HPP
#define TYPES_HPP
#include "partexpression.hpp"

namespace piyavkin
{
  struct InputType
  {
    union input_t
    {
      detail::Operand operand;
      detail::Operation operation;
      detail::Bracket bracket;
    };
    input_t symbol;
    detail::TypesPartsExpression type;
  };
  struct Postfix
  {
    union postfix_t
    {
      detail::Operand operand;
      detail::Operation operation;
    };
    postfix_t symbol;
    detail::TypesPartsExpression type;
  };
  struct ConversionExpressionType
  {
    union conversion_t
    {
      detail::Bracket bracket;
      detail::Operation operation;
    };
    conversion_t symbol;
    detail::TypesPartsExpression type;
  };
}
#endif
