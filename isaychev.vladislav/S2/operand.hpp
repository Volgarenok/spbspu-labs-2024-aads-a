#ifndef OPERAND_HPP
#define OPERAND_HPP

namespace isaychev
{
  class Operand
  {
   public:
    explicit Operand(long long int n);

    long long int get_operand() const noexcept;

   private:
    long long int op_;
  };
}

#endif
