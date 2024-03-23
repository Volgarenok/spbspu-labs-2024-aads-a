#ifndef TOKENS_HPP
#define TOKENS_HPP
#include "operators.hpp"

namespace zaitsev
{
  enum struct token_type { bracket = 0, binary_operator, value };
  enum struct bracket_type { round_open = 1 , round_close = -1 };

  template<typename T>
  union TokenValue
  {
    bracket_type bracket;
    BinaryOperator<T>* bin_operator;
    T value;
  };

  template<typename T>
  struct Token
  {
    token_type type;
    TokenValue<T> token;
  };
}
#endif
