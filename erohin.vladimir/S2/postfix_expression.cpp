#include "postfix_expression.hpp"
#include <stdexcept>
#include <iostream>
#include "stack.hpp"

erohin::PostfixExpression::PostfixExpression(const expression_t & inf_expr)
{
  try
  {
    convertInfixToPostfix(expression, inf_expr);
  }
  catch (...)
  {
    while (!expression.empty())
    {
      expression.pop();
    }
    throw;
  }
}

bool erohin::PostfixExpression::empty() const
{
  return expression.empty();
}

erohin::Operand erohin::PostfixExpression::evaluate() const
{
  Stack< Token > temp_stack;
  Queue< Token > init_queue(expression);
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
          throw std::runtime_error("Extra binary operator in postfix expression");
        }
        top_operand[i] = temp_stack.top().token.operand;
        temp_stack.pop();
      }
      Operand result = current.token.operation.evaluate(top_operand[1], top_operand[0]);
      temp_stack.push(Token{ token_identifier_t::OPERAND_TYPE, result });
    }
    init_queue.pop();
  }
  Operand result = temp_stack.top().token.operand;
  temp_stack.pop();
  if (!temp_stack.empty())
  {
    throw std::runtime_error("Extra operand in postfix expression");
  }
  return result;
}

void erohin::convertInfixToPostfix(Queue< Token > & post_expr, Queue< Token > inf_expr)
{
  Stack< Token > temp_stack;
  bool isOpenBracketPrevious = false;
  while (!inf_expr.empty())
  {
    Token & current = inf_expr.front();
    switch (current.id)
    {
    case operand_token:
      post_expr.push(current);
      inf_expr.pop();
      isOpenBracketPrevious = false;
      break;
    case bracket_token:
      if (current.token.bracket.bracket_type == open_bt)
      {
        temp_stack.push(current);
        isOpenBracketPrevious = true;
      }
      else if (current.token.bracket.bracket_type == close_bt)
      {
        if (temp_stack.empty())
        {
          throw std::runtime_error("An extra bracket in postfix expression record");
        }
        if (isOpenBracketPrevious)
        {
          throw std::runtime_error("Empty brackets were found");
        }
        Token & top = temp_stack.top();
        while (!(top.id == bracket_token && top.token.bracket.bracket_type == open_bt))
        {
          post_expr.push(top);
          temp_stack.pop();
          if (temp_stack.empty())
          {
            throw std::runtime_error("An extra bracket in postfix expression record");
          }
          top = temp_stack.top();
        }
        temp_stack.pop();
      }
      inf_expr.pop();
      break;
    case operator_token:
      if (temp_stack.empty())
      {
        temp_stack.push(current);
        inf_expr.pop();
        break;
      }
      Token & top = temp_stack.top();
      while ((top.id == operator_token) && (current.token.operation >= top.token.operation))
      {
        post_expr.push(top);
        temp_stack.pop();
        if (!temp_stack.empty())
        {
          top = temp_stack.top();
        }
        else
        {
          break;
        }
      }
      temp_stack.push(current);
      inf_expr.pop();
      break;
    }
  }
  while (!temp_stack.empty() && temp_stack.top().id == operator_token)
  {
    post_expr.push(temp_stack.top());
    temp_stack.pop();
  }
  if (!temp_stack.empty())
  {
    throw std::runtime_error("One extra bracket in postfix expression record");
  }
}

void erohin::inputPostfixExpressionLines(std::istream & input, Queue< PostfixExpression > & expr_lines)
{
  while (!input.eof())
  {
    expression_t current_expr;
    inputInfixExpression(input, current_expr);
    if (!current_expr.empty())
    {
      expr_lines.push(PostfixExpression(current_expr));
    }
  }
}
