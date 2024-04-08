#include "conversion.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include "calculations.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"

strelyaev::Queue< strelyaev::detail::ExpressionUnit > strelyaev::makeQueue(std::istream& input)
{
  strelyaev::Queue< strelyaev::detail::ExpressionUnit > token_queue;
  strelyaev::Queue< char > raw_data;
  char c = 0;
  std::cout << "============MAKE=============\n";
  input >> std::noskipws;
  while (input >> c)
  {
    if (c == '\n')
    {
      break;
    }
    else
    {
      std::cout << "ПУШУ:(" << c << ")\n";
      raw_data.push(c);
    }
  }
  input >> std::skipws;
  int i = 0; // TO DEL
  while (!raw_data.empty())
  {
    i++;
    std::cout << i << ":" << raw_data.drop() << ":\n";
  }
  std::cout << "\n============END_MAKE=============\n";
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
  //strelyaev::Queue< strelyaev::detail::ExpressionUnit > postfix_units_queue = strelyaev::makePostfix(infix_units_queue);
  //long long result = calculatePostfix(postfix_units_queue);
  //return result;
}