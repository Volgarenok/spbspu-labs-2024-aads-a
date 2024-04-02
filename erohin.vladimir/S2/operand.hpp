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
    long long operator()();
  private:
    long long numeric_;
  };
}

#endif
