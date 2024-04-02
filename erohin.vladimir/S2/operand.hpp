#ifndef OPERAND_HPP
#define OPERAND_HPP

namespace erohin
{
  class Operand
  {
  public:
    Operand();
    Operand(long long number);
    ~Operand() = default;
    long long operator()() const;
  private:
    long long numeric_;
  };
}

#endif
