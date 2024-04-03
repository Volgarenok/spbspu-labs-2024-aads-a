#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <cstddef>

namespace novokhatskiy
{
  
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
  union Expression
  {
    Expression() = default;
    Expression(size_t value);
    Expression(char scope);
    //Expression(char symb);

    Operand operand;
    Bracket bracket;
    Operation operation;
  };

  struct InfixType
  {
    InfixType() = default;
    InfixType(PartsOfExpression type, char scope);
    InfixType(PartsOfExpression type, size_t value);
    
    Expression data_;
    PartsOfExpression type_;
  };
}

#endif
