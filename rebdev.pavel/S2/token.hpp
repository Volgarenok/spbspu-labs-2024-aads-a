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

    data() = default;
    data(const data & d) = default;
    data(data && d) = default;
    data(long long num);
    data(char oper);
    data & operator=(const data & d) = default;
    data & operator=(data && d) = default;
    ~data() = default;
  };

  class token
  {
    public:
      token() = default;
      token(char oper);
      token(long long num);
      token(const token & t);
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
