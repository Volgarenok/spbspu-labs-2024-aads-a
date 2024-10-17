#ifndef OPERAND_HPP
#define OPERAND_HPP

namespace baranov
{
  class Operand
  {
  public:
    Operand() = default;
    explicit Operand(long long int value);
    long long int getValue() const;
  private:
    long long int value_;
  };
}

#endif

