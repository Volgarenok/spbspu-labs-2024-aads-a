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
    //PartsOfExpression part_;
  };
  enum class PartsOfExpression
  {
    operand = 0,
    operation = 1,
    openBracket = 2,
    closedBracket = 3
  };
  
  struct Operand
  {
  public:
    Operand() = default;
    explicit Operand(size_t value);
    size_t getOperand() const noexcept;

  private:
    size_t value_;
  };

  struct Operation
  {
  public:
    Operation() = default;
    explicit Operation(char symb);
    char getOperation() const;

  private:
    char operation_;
  };

  struct Bracket
  {
  public:
    Bracket() = default;
    explicit Bracket(char symb);
    PartsOfExpression getBracket() const noexcept;
  private:
    PartsOfExpression type_;
  };
}

#endif
