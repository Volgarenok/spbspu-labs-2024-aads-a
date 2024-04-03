#include "postfix_expression.hpp"
#include <stdexcept>

#include <stack>

erohin::PostfixExpression::PostfixExpression(const InfixExpression & inf_expr)
{
  InfixToPostfix(expression, inf_expr);
}

erohin::Operand erohin::PostfixExpression::evaluate() const
{
  return Operand();
}

void erohin::InfixToPostfix(std::queue< Token > & post_expr, std::queue< Token > inf_expr)
{
  constexpr auto close_bt = bracket_t::CLOSE_BRACKET;
  constexpr auto open_bt = bracket_t::OPEN_BRACKET;
  constexpr auto bracket_token = token_identifier_t::BRACKET_TYPE;
  constexpr auto operand_token = token_identifier_t::OPERAND_TYPE;
  constexpr auto operator_token = token_identifier_t::OPERATOR_TYPE;
  std::stack< Token > temp_stack;
  while (!inf_expr.empty())
  {
    Token & current = inf_expr.front();
    switch (current.id)
    {
      case operand_token:
        post_expr.push(current);
        inf_expr.pop();
        break;
      case bracket_token:
        if (current.token.bracket.bracket_type == open_bt)
        {
          temp_stack.push(current);
          inf_expr.pop();
        }
        else if (current.token.bracket.bracket_type == close_bt)
        {
          Token & top = temp_stack.top();
          while (top.id != bracket_token && top.token.bracket.bracket_type == open_bt)
          {
            if ((top.id != bracket_token && top.token.bracket.bracket_type == close_bt) || temp_stack.empty())
            {
              throw std::runtime_error("Error in postfix expression record");
            }
            post_expr.push(top);
            temp_stack.pop();
          }
        }
        break;
      case operator_token:
        Token & top = temp_stack.top();
        while (top.id == operator_token && current.token.operation >= top.token.operation && !temp_stack.empty())
        {
          top = temp_stack.top();
          post_expr.push(top);
          temp_stack.pop();
        }
        temp_stack.push(current);
        inf_expr.pop();
        break;
    }
  }
}
