#ifndef TYPES_HPP
#define TYPES_HPP
#include <cstddef>
#include "partexpression.hpp"

namespace piyavkin
{
  using namespace detail;
  struct InputType
  {
  public:
    InputType();
    explicit InputType(unsigned long long val);
    InputType(char val, size_t num);
    TypesPartsExpression getType();
    char getBraket();
    char getOperation();
    unsigned long long getOperand();
  private:
    union
    {
      Operand operand;
      Operation operation;
      Bracket bracket;
    };
    TypesPartsExpression type;
  };
  struct Postfix
  {
  public:
    Postfix();
    explicit Postfix(unsigned long long val);
    explicit Postfix(char val);
    TypesPartsExpression getType();
    char getOperation();
    unsigned long long getOperand();
  private:
    union
    {
      Operand operand;
      Operation operation;
    };
    TypesPartsExpression type;
  };
  struct ConversionExpressionType
  {
  public:
    ConversionExpressionType();
    ConversionExpressionType(char val, size_t num);
    TypesPartsExpression getType();
    char getBraket();
    char getOperation();
  private:
    union
    {
      Bracket bracket;
      Operation operation;
    };
    TypesPartsExpression type;
  };
}
#endif
