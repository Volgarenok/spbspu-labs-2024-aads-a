#ifndef TYPES_HPP
#define TYPES_HPP
#include <cstddef>
#include "partexpression.hpp"

namespace piyavkin
{
  struct InputType
  {
  public:
    InputType();
    explicit InputType(unsigned long long val);
    InputType(char val, size_t num);
  // private:
    union
    {
      detail::Operand operand;
      detail::Operation operation;
      detail::Bracket bracket;
    };
    detail::TypesPartsExpression type;
  };
  struct Postfix
  {
  public:
    Postfix();
    Postfix(unsigned long long val);
    Postfix(char val);
  private:
    union
    {
      detail::Operand operand;
      detail::Operation operation;
    };
    detail::TypesPartsExpression type;
  };
  struct ConversionExpressionType
  {
  public:
    ConversionExpressionType();
    ConversionExpressionType(char val, size_t num);
  private:
    union
    {
      detail::Bracket bracket;
      detail::Operation operation;
    };
    detail::TypesPartsExpression type;
  };
}
#endif
