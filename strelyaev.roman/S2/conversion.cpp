#include "conversion.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "calculations.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"

strelyaev::Queue< strelyaev::detail::ExpressionUnit > strelyaev::makeQueue(std::istream& input)
{
  std::string temp_string = "";
  std::getline(input, temp_string);
  if (temp_string.size() < 2)
  {
    throw std::length_error("New line is met");
  }
  std::istringstream in(temp_string);
  strelyaev::Queue< strelyaev::detail::ExpressionUnit > token_queue;
  std::string str = "";
  while (in >> str)
  {
    strelyaev::detail::TokenType type = strelyaev::detail::TokenType::NONE;
    strelyaev::detail::Token new_token;
    char ch = 0;
    if (strelyaev::isOperation(str))
    {
      ch = str[0];
      new_token = strelyaev::detail::Token(ch);
      type = strelyaev::detail::TokenType::OPERATION;
    }
    else if (strelyaev::isBracket(str))
    {
      ch = str[0];
      new_token = strelyaev::detail::Token(ch);
      type = strelyaev::detail::TokenType::BRACKET;
    }
    else
    {
      long long operand = 0;
      try
      {
        operand = std::stoll(str);
      }
      catch (const std::exception& e)
      {
        continue;
      }
      new_token = strelyaev::detail::Token(operand);
      type = strelyaev::detail::TokenType::OPERAND;
    }
    strelyaev::detail::ExpressionUnit new_unit{new_token, type};
    token_queue.push(new_unit);
  }
  return token_queue;
}

strelyaev::Queue< strelyaev::detail::ExpressionUnit > strelyaev::makePostfix(Queue< detail::ExpressionUnit >& queue)
{
  strelyaev::Stack< strelyaev::detail::ExpressionUnit > temp_stack;
  strelyaev::Queue< strelyaev::detail::ExpressionUnit > postfix_queue;
  while (!queue.empty())
  {
    strelyaev::detail::ExpressionUnit unit = queue.drop();
    if (unit.type == strelyaev::detail::TokenType::OPERAND)
    {
      postfix_queue.push(unit);
    }
    if (unit.type == strelyaev::detail::TokenType::BRACKET)
    {
      if (unit.token.operation == '(')
      {
        temp_stack.push(unit);
      }
      if (unit.token.operation == ')')
      {
        strelyaev::detail::ExpressionUnit stack_peek = temp_stack.drop();
        while (stack_peek.token.operation != '(')
        {
          postfix_queue.push(stack_peek);
          stack_peek = temp_stack.drop();
        }
      }
    }
    if (unit.type == strelyaev::detail::TokenType::OPERATION)
    {
      if (temp_stack.empty())
      {
        temp_stack.push(unit);
        continue;
      }
      strelyaev::detail::ExpressionUnit stack_peek = temp_stack.drop();
      if (strelyaev::getPrecedence(unit.token.operation) > strelyaev::getPrecedence(stack_peek.token.operation))
      {
        temp_stack.push(stack_peek);
        temp_stack.push(unit);
      }
      else if (strelyaev::getPrecedence(unit.token.operation) <= strelyaev::getPrecedence(stack_peek.token.operation))
      {
        while (strelyaev::getPrecedence(unit.token.operation) <= strelyaev::getPrecedence(stack_peek.token.operation))
        {
          postfix_queue.push(stack_peek);
          if (temp_stack.empty())
          {
            break;
          }
          stack_peek = temp_stack.drop();
        }
        if (!temp_stack.empty())
        {
          temp_stack.push(stack_peek);
        }
        temp_stack.push(unit);
      }
    }
  }
  while (!temp_stack.empty())
  {
    strelyaev::detail::ExpressionUnit unit = temp_stack.drop();
    postfix_queue.push(unit);
  }
  return postfix_queue;
}

long long strelyaev::calculatePostfix(strelyaev::Queue< strelyaev::detail::ExpressionUnit >& queue)
{
  strelyaev::Stack< long long > processing_stack;
  while (!queue.empty())
  {
    strelyaev::detail::ExpressionUnit unit = queue.drop();
    if (unit.type == strelyaev::detail::TokenType::OPERAND)
    {
      processing_stack.push(unit.token.operand);
    }
    if (unit.type == strelyaev::detail::TokenType::OPERATION)
    {
      long long second = processing_stack.drop();
      if (processing_stack.empty())
      {
        throw std::logic_error("Something is wrong with postfix expression");
      }
      long long first = processing_stack.drop();
      long long result = calculateOperation(first, second, unit.token.operation);
      processing_stack.push(result);
    }
  }
  long long result = processing_stack.drop();
  if (!processing_stack.empty())
  {
    throw std::logic_error("Something is wrong with postfix expression");
  }
  return result;
}

long long strelyaev::calculateInfixExpression(std::istream& in)
{
  strelyaev::Queue< strelyaev::detail::ExpressionUnit > infix_units_queue = strelyaev::makeQueue(in);
  strelyaev::Queue< strelyaev::detail::ExpressionUnit > postfix_units_queue = strelyaev::makePostfix(infix_units_queue);
  long long result = calculatePostfix(postfix_units_queue);
  return result;
}