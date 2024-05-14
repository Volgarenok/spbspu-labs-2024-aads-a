#include "token.hpp"
#include <stdexcept>
#include "operators.hpp"

bool zaitsev::areBraketsPaired(const Token& lhs, const Token& rhs)
{
  bool both_brackets = (lhs.type_ == token_type::bracket && rhs.type_ == token_type::bracket);
  return (both_brackets && (static_cast< int >(lhs.value_.bracket_) + static_cast< int >(rhs.value_.bracket_) == 0));
}

size_t binOperatorPriority(const zaitsev::Token& token)
{
  using namespace zaitsev;
  switch (token.value_.bin_operator_)
  {
  case bin_operator_type::plus:
  case bin_operator_type::minus:
    return 1;
  case bin_operator_type::mult:
  case bin_operator_type::div:
  case bin_operator_type::mod:
    return 2;
  default:
    return 0;
  }
}

bool zaitsev::lessBinOperatorPriority(const Token& lhs, const Token& rhs)
{
  return binOperatorPriority(lhs) < binOperatorPriority(rhs);
}

long long zaitsev::binOperatorResult(const Token& bin_operator, long long a, long long b)
{
  switch (bin_operator.value_.bin_operator_)
  {
  case bin_operator_type::plus:
    return safePlus(a, b);
  case bin_operator_type::minus:
    return safeMinus(a, b);
  case bin_operator_type::mult:
    return safeMult(a, b);
  case bin_operator_type::div:
    return safeDiv(a, b);
  case bin_operator_type::mod:
    return safeMod(a, b);
  default:
    throw std::invalid_argument("Invalid arguments");
  }
}
