#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "primaryType.hpp"

namespace zhalilov
{
  class Operand
  {
  public:
    explicit Operand(long long);
    PrimaryType getPrimaryType() const;
    long long getNum() const;
  private:
    long long num_;
  };
}

#endif
