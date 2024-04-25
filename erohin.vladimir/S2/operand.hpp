#ifndef OPERAND_HPP
#define OPERAND_HPP

namespace erohin
{
  class Operand
  {
  public:
    using value_type = long long;
    Operand();
    Operand(value_type  number);
    ~Operand() = default;
    value_type operator()() const;
  private:
    value_type numeric_;
  };
}

#endif
