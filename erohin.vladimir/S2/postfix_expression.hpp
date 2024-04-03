#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIC_EXPRESSION_HPP

#include <queue>
#include <stack>
#include <iosfwd>
#include "infix_expression.hpp"

namespace erohin
{

  constexpr auto close_bt = bracket_t::CLOSE_BRACKET;
  constexpr auto open_bt = bracket_t::OPEN_BRACKET;
  constexpr auto bracket_token = token_identifier_t::BRACKET_TYPE;
  constexpr auto operand_token = token_identifier_t::OPERAND_TYPE;
  constexpr auto operator_token = token_identifier_t::OPERATOR_TYPE;

  struct PostfixExpression
  {
    PostfixExpression() = default;
    PostfixExpression(const std::queue< Token > & inf_expr);
    ~PostfixExpression() = default;
    Operand evaluate() const;
    std::queue< Token > expression;
  };

  void convertInfixToPostfix(std::queue< Token > & post_expr, std::queue< Token > inf_expr);
  void inputPostfixExpressionLines(std::istream & input, std::queue< PostfixExpression > & expr_lines);
}

#endif
