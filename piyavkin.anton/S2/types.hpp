#ifndef TYPES_HPP
#define TYPES_HPP
#include <cstddef>
#include "partexpression.hpp"

namespace piyavkin
{
  struct InputType
  {
    InputType();
    InputType(long long val);
    InputType(char val, size_t num);
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
    Postfix(long long val);
    Postfix(char val);
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
    ConversionExpressionType(char val, size_t num);
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
