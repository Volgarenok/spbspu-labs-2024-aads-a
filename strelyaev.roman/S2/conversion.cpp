#include "conversion.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include "calculations.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"

strelyaev::ExpressionUnit strelyaev::convertStringToUnit(std::string string_token)
{
  strelyaev::Token new_token;
  strelyaev::TokenType type = strelyaev::TokenType::NONE;
  if (string_token.size() == 0)
  {
    throw std::logic_error("empty string_token");
  }
  try
  {
    long long operand = std::stoll(string_token);
    new_token = strelyaev::Token(operand);
    type = strelyaev::TokenType::OPERAND;
  }
  catch(...)
  {
    char c = string_token[0];
    new_token = strelyaev::Token(c);
    if (strelyaev::isBracket(string_token))
    {
      type = strelyaev::TokenType::BRACKET;
    }
    if (strelyaev::isOperation(string_token))
    {
      type = strelyaev::TokenType::OPERATION;
    }
  }
  strelyaev::ExpressionUnit new_unit(new_token, type);
  return new_unit;
}

strelyaev::Queue< strelyaev::ExpressionUnit > strelyaev::parseString(std::istream& input)
{
  strelyaev::Queue< strelyaev::ExpressionUnit > queue_of_eu;
  std::string line = "";
  std::string token_string = "";
  std::getline(input, line);
  strelyaev::ExpressionUnit unit;
  for (char c : line)
  {
    if (c == ' ' || c == '\0')
    {
      unit = convertStringToUnit(token_string);
      queue_of_eu.push(unit);
      token_string = "";
      continue;
    }
    token_string += c;
  }
  if (!token_string.empty())
  {
    unit = convertStringToUnit(token_string);
    queue_of_eu.push(unit);
  }
  return queue_of_eu;
}

strelyaev::Queue< strelyaev::ExpressionUnit > strelyaev::makePostfix(Queue< ExpressionUnit >& queue)
{
  strelyaev::Stack< strelyaev::ExpressionUnit > temp_stack;
  strelyaev::Queue< strelyaev::ExpressionUnit > postfix_queue;
  while (!queue.empty())
  {
    strelyaev::ExpressionUnit unit = queue.front();
    queue.pop_front();
    if (unit.getType() == strelyaev::TokenType::OPERAND)
    {
      postfix_queue.push(unit);
    }
    if (unit.getType() == strelyaev::TokenType::BRACKET)
    {
      if (unit.getOperation() == '(')
      {
        temp_stack.push(unit);
      }
      if (unit.getOperation() == ')')
      {
        strelyaev::ExpressionUnit stack_peek = temp_stack.back();
        temp_stack.pop_back();
        while (stack_peek.getOperation() != '(')
        {
          postfix_queue.push(stack_peek);
          stack_peek = temp_stack.back();
          temp_stack.pop_back();
        }
      }
    }
    if (unit.getType() == strelyaev::TokenType::OPERATION)
    {
      if (temp_stack.empty())
      {
        temp_stack.push(unit);
        continue;
      }
      strelyaev::ExpressionUnit stack_peek = temp_stack.back();
      temp_stack.pop_back();
      if (!(strelyaev::isPrecedenceLess(unit.getOperation(), stack_peek.getOperation())))
      {
        temp_stack.push(stack_peek);
        temp_stack.push(unit);
      }
      else if (strelyaev::isPrecedenceLess(unit.getOperation(), stack_peek.getOperation()))
      {
        while (strelyaev::isPrecedenceLess(unit.getOperation(), stack_peek.getOperation()))
        {
          postfix_queue.push(stack_peek);
          if (temp_stack.empty())
          {
            break;
          }
          stack_peek = temp_stack.back();
          temp_stack.pop_back();
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
    strelyaev::ExpressionUnit unit = temp_stack.back();
    temp_stack.pop_back();
    postfix_queue.push(unit);
  }
  return postfix_queue;
}

long long strelyaev::calculatePostfix(strelyaev::Queue< strelyaev::ExpressionUnit >& queue)
{
  strelyaev::Stack< ExpressionUnit > processing_stack;
  if (queue.empty())
  {
    throw std::out_of_range("Empty queue is met");
  }
  while (!queue.empty())
  {
    strelyaev::ExpressionUnit unit = queue.front();
    queue.pop_front();
    if (unit.getType() == strelyaev::TokenType::OPERAND)
    {
      processing_stack.push(unit);
    }
    if (unit.getType() == strelyaev::TokenType::OPERATION)
    {
      ExpressionUnit second = processing_stack.back();
      processing_stack.pop_back();
      if (processing_stack.empty())
      {
        throw std::invalid_argument("Something is wrong with postfix expression");
      }
      ExpressionUnit first = processing_stack.back();
      processing_stack.pop_back();
      long long result = calculateOperation(first, second, unit);
      Token temp_token(result);
      ExpressionUnit operand_unit(temp_token, strelyaev::TokenType::OPERAND);
      processing_stack.push(operand_unit);
    }
  }
  ExpressionUnit result = processing_stack.back();
  processing_stack.pop_back();
  if (!processing_stack.empty())
  {
    throw std::invalid_argument("Something is wrong with postfix expression");
  }
  return result.getOperand();
}



