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
  Token new_token;
  TokenType type = TokenType::NONE;
  try
  {
    long long operand = std::stoll(string_token);
    new_token = Token(operand);
    type = TokenType::OPERAND;
  }
  catch (...)
  {
    if (isBracket(string_token))
    {
      type = TokenType::BRACKET;
    }
    if (isOperation(string_token))
    {
      type = TokenType::OPERATION;
    }
    new_token = Token(string_token[0]);
  }
  strelyaev::ExpressionUnit new_unit(new_token, type);
  return new_unit;
}

strelyaev::Queue< strelyaev::ExpressionUnit > strelyaev::parseString(std::istream& input)
{
  Queue< ExpressionUnit > queue_of_eu;
  std::string line = "";
  std::getline(input, line);
  ExpressionUnit unit;
  std::string delimiter = " ";
  size_t pos = 0;
  std::string token;
  while ((pos = line.find(delimiter)) != std::string::npos)
  {
    token = line.substr(0, pos);
    unit = convertStringToUnit(token);
    line.erase(0, pos + delimiter.length());
    queue_of_eu.push(unit);
  }
  unit = convertStringToUnit(line);
  queue_of_eu.push(unit);
  return queue_of_eu;
}

strelyaev::Queue< strelyaev::ExpressionUnit > strelyaev::makePostfix(Queue< ExpressionUnit >& queue)
{
  Stack< ExpressionUnit > temp_stack;
  Queue< ExpressionUnit > postfix_queue;
  while (!queue.empty())
  {
    ExpressionUnit unit = queue.front();
    queue.pop_front();
    if (unit.getType() == TokenType::OPERAND)
    {
      postfix_queue.push(unit);
    }
    if (unit.getType() == TokenType::BRACKET)
    {
      if (unit.getOperation() == '(')
      {
        temp_stack.push(unit);
      }
      if (unit.getOperation() == ')')
      {
        ExpressionUnit stack_peek = temp_stack.back();
        temp_stack.pop_back();
        while (stack_peek.getOperation() != '(')
        {
          postfix_queue.push(stack_peek);
          stack_peek = temp_stack.back();
          temp_stack.pop_back();
        }
      }
    }
    if (unit.getType() == TokenType::OPERATION)
    {
      if (temp_stack.empty())
      {
        temp_stack.push(unit);
        continue;
      }
      ExpressionUnit stack_peek = temp_stack.back();
      temp_stack.pop_back();
      if (!(unit <= stack_peek))
      {
        temp_stack.push(stack_peek);
        temp_stack.push(unit);
      }
      else if (unit <= stack_peek)
      {
        while (unit <= stack_peek)
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
    ExpressionUnit unit = temp_stack.back();
    temp_stack.pop_back();
    postfix_queue.push(unit);
  }
  return postfix_queue;
}

long long strelyaev::calculatePostfix(strelyaev::Queue< strelyaev::ExpressionUnit >& queue)
{
  Stack< ExpressionUnit > processing_stack;
  if (queue.empty())
  {
    throw std::out_of_range("Empty queue is met");
  }
  while (!queue.empty())
  {
    ExpressionUnit unit = queue.front();
    queue.pop_front();
    if (unit.getType() == TokenType::OPERAND)
    {
      processing_stack.push(unit);
    }
    if (unit.getType() == TokenType::OPERATION)
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
      ExpressionUnit operand_unit(temp_token, TokenType::OPERAND);
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

