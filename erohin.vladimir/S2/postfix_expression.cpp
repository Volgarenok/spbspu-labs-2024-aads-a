#include "postfix_expression.hpp"
#include <stdexcept>

#include <stack>

erohin::PostfixExpression::PostfixExpression(const std::queue< Token > & inf_expr)
{
  InfixToPostfix(expression, inf_expr);
}

erohin::Operand erohin::PostfixExpression::evaluate() const
{
  std::stack< Token > temp_stack;
  std::queue< Token > init_queue(expression);
  while (!init_queue.empty())
  {
    Token & current = init_queue.front();
    if (current.id == operand_token)
    {
      temp_stack.push(current);
    }
    else if (current.id == operator_token)
    {
      Operand top_operand[2];
      for (int i = 0; i < 2; ++i)
      {
        if (temp_stack.empty())
        {
          throw std::runtime_error("Error in postfix expression evaluating");
        }
        top_operand[i] = temp_stack.top().token.operand;
        temp_stack.pop();
      }
      Operand result = current.token.operation.evaluate(top_operand[0], top_operand[1]);
      temp_stack.push(Token{ token_identifier_t::OPERAND_TYPE, result });
    }
    init_queue.pop();
  }
  return temp_stack.top().token.operand;
}

void erohin::InfixToPostfix(std::queue< Token > & post_expr, std::queue< Token > inf_expr)
{
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
    inf_expr.pop();
  }
}
