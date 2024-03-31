#ifndef BINARYOPERATOR_HPP
#define BINARYOPERATOR_HPP

#include "primaryType.hpp"

namespace zhalilov
{
  class Operand;

  class BinOperator
  {
  public:
    enum class Type
    {
      Undefined,
      Add,
      Subtraction,
      Multiply,
      Division,
      Mod
    };

    BinOperator();
    explicit BinOperator(Type);
    explicit BinOperator(char symb);
    Operand operator()(const Operand &, const Operand &) const;

    bool operator<(const BinOperator &other) const;
    bool operator>(const BinOperator &other) const;
    bool operator==(const BinOperator &other) const;
    bool operator!=(const BinOperator &other) const;
    bool operator<=(const BinOperator &other) const;
    bool operator>=(const BinOperator &other) const;

    unsigned short getPriority() const;

  private:
    Type type_;
  };
}

#endif
