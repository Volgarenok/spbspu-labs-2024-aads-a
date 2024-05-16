#ifndef TOKENS_HPP
#define TOKENS_HPP

namespace zaitsev
{
  enum struct token_type
  {
    undefined = 0,
    bracket,
    bin_operator,
    numeric
  };
  enum struct bracket_type
  {
    round_open = 1,
    round_close = -1
  };
  enum struct bin_operator_type
  {
    plus,
    minus,
    mult,
    div,
    mod
  };

  union TokenValue
  {
    bracket_type bracket_;
    bin_operator_type bin_operator_;
    long long numeric_;
  };

  struct Token
  {
    Token():
      type_(token_type::undefined),
      value_()
    {}
    Token(token_type type, TokenValue value):
      type_(type),
      value_(value)
    {}
    Token(const Token& other) = default;
    Token(Token&& other) = default;
    const token_type type_;
    const TokenValue value_;
  };
  bool lessBinOperatorPriority(const Token& lhs, const Token& rhs);
  bool areBraketsPaired(const Token& lhs, const Token& rhs);
  long long binOperatorResult(const Token& bin_operator, long long a, long long b);
}
#endif
