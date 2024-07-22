#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

#include "mathOperator.hpp"

namespace rebdev
{
  union data
  {
    long long num_;
    mathOperator oper_;
  };

  class token
  {
    public:
      token(char oper);
      token(long long num);
      token operator()(token f, token s);
      long long getNum() const noexcept;
      bool isNum() const noexcept;
      unsigned int priority() const noexcept;
      bool leftBracket() const noexcept;
    private:
      data data_;
      bool isNum_;
  };
}

#endif
