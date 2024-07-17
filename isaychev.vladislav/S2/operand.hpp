#ifndef OPERAND_HPP
#define OPERAND_HPP

namespace isaychev
{
  class Operand
  {
   public:
    Operand();
    explicit Operand(long long int n);

    void set_operand(long long int n);
    long long int get_operand() const;

   private:
    long long int op_;
  };
}

#endif
