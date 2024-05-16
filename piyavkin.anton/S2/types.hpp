#ifndef TYPES_HPP
#define TYPES_HPP
#include <cstddef>

namespace piyavkin
{
  namespace detail
  {
    enum TypesPartsExpression
    {
      operand,
      operation,
      bracket
    };
  }
  class PartsExpression
  {
    friend struct InputType;
    friend struct Postfix;
    friend struct ConversionExpressionType;
  public:
    PartsExpression(unsigned long long val);
    PartsExpression(char val, size_t num);
  private:
    struct Operand
    {
      explicit Operand(unsigned long long val);
      unsigned long long number;
    };
    struct Operation
    {
      explicit Operation(char val);
      bool operator>(const Operation& rhs);
      char operation;
    };
    struct Bracket
    {
      explicit Bracket(char val);
      char bracket;
    };
    union InputT
    {
      InputT();
      Operand operand;
      Operation operation;
      Bracket bracket;
    };
    union PostfixT
    {
      PostfixT();
      Operand operand;
      Operation operation;
    };
    union ConversionT
    {
      ConversionT();
      Operation operation;
      Bracket bracket;
    };
    union
    {
      ConversionT conversionPart;
      PostfixT postfixPart;
      InputT part;
    };
  };
  using namespace detail;
  struct InputType
  {
  public:
    InputType();
    explicit InputType(unsigned long long val);
    InputType(char val, size_t num);
    TypesPartsExpression getType() const;
    char getBraket() const;
    char getOperation() const;
    unsigned long long getOperand() const;
  private:
    PartsExpression value;
    TypesPartsExpression type;
  };
  struct Postfix
  {
  public:
    Postfix();
    explicit Postfix(unsigned long long val);
    explicit Postfix(char val);
    TypesPartsExpression getType() const;
    char getOperation() const;
    unsigned long long getOperand() const;
  private:
    PartsExpression value;
    TypesPartsExpression type;
  };
  struct ConversionExpressionType
  {
  public:
    ConversionExpressionType();
    ConversionExpressionType(char val, size_t num);
    TypesPartsExpression getType() const;
    char getBraket() const;
    char getOperation() const;
  private:
    PartsExpression value;
    TypesPartsExpression type;
  };
  TypesPartsExpression getType(char symbol);
  TypesPartsExpression getType(unsigned long long);
}
#endif
