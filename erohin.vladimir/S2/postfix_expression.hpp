#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIC_EXPRESSION_HPP

#include <iosfwd>
#include "queue.hpp"
#include "stack.hpp"
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
    expression_t expression;
    PostfixExpression() = default;
    PostfixExpression(const expression_t & inf_expr);
    ~PostfixExpression() = default;
    bool empty() const;
    Operand evaluate() const;
  };

  void convertInfixToPostfix(expression_t & post_expr, expression_t inf_expr);
  void inputPostfixExpressionLines(std::istream & input, Queue< PostfixExpression > & expr_lines);
}

#endif
