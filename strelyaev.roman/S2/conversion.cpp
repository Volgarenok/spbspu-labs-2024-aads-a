#include "conversion.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "calculations.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"

strelyaev::Queue< strelyaev::ExpressionUnit > strelyaev::makeQueue(std::istream& input)
{
  std::string temp_string = "";
  std::getline(input, temp_string);
  if (temp_string.size() < 2)
  {
    throw std::length_error("New line is met");
  }
  std::istringstream in(temp_string);
  strelyaev::Queue< strelyaev::ExpressionUnit > token_queue;
  std::string str = "";
  while (in >> str)
  {
    strelyaev::TokenType type = strelyaev::TokenType::NONE;
    strelyaev::Token new_token;
    char ch = 0;
    if (strelyaev::isOperation(str))
    {
      ch = str[0];
      new_token = strelyaev::Token(ch);
      type = strelyaev::TokenType::OPERATION;
    }
    else if (strelyaev::isBracket(str))
    {
      ch = str[0];
      new_token = strelyaev::Token(ch);
      type = strelyaev::TokenType::BRACKET;
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
      new_token = strelyaev::Token(operand);
      type = strelyaev::TokenType::OPERAND;
    }
    strelyaev::ExpressionUnit new_unit{new_token, type};
    token_queue.push(new_unit);
  }
  return token_queue;
}

strelyaev::Queue< strelyaev::ExpressionUnit > strelyaev::makePostfix(Queue< ExpressionUnit >& queue)
{
  strelyaev::Stack< strelyaev::ExpressionUnit > temp_stack;
  strelyaev::Queue< strelyaev::ExpressionUnit > postfix_queue;
  while (!queue.empty())
  {
    strelyaev::ExpressionUnit unit = queue.drop();
    if (unit.type == strelyaev::TokenType::OPERAND)
    {
      postfix_queue.push(unit);
    }
    if (unit.type == strelyaev::TokenType::BRACKET)
    {
      if (unit.token.operation == '(')
      {
        temp_stack.push(unit);
      }
      if (unit.token.operation == ')')
      {
        strelyaev::ExpressionUnit stack_peek = temp_stack.drop();
        while (stack_peek.token.operation != '(')
        {
          postfix_queue.push(stack_peek);
          stack_peek = temp_stack.drop();
        }
      }
    }
    if (unit.type == strelyaev::TokenType::OPERATION)
    {
      if (temp_stack.empty())
      {
        temp_stack.push(unit);
        continue;
      }
      strelyaev::ExpressionUnit stack_peek = temp_stack.drop();
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
    strelyaev::ExpressionUnit unit = temp_stack.drop();
    postfix_queue.push(unit);
  }
  return postfix_queue;
}

long long strelyaev::calculatePostfix(strelyaev::Queue< strelyaev::ExpressionUnit >& queue)
{
  strelyaev::Stack< long long > processing_stack;
  while (!queue.empty())
  {
    strelyaev::ExpressionUnit unit = queue.drop();
    if (unit.type == strelyaev::TokenType::OPERAND)
    {
      processing_stack.push(unit.token.operand);
    }
    if (unit.type == strelyaev::TokenType::OPERATION)
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
  strelyaev::Queue< strelyaev::ExpressionUnit > infix_units_queue = strelyaev::makeQueue(in);
  strelyaev::Queue< strelyaev::ExpressionUnit > postfix_units_queue = strelyaev::makePostfix(infix_units_queue);
  long long result = calculatePostfix(postfix_units_queue);
  return result;
}