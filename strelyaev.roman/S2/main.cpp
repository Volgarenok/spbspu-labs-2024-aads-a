#include <iostream>
#include "queue.hpp"
#include "stack.hpp"
#include <fstream>
#include "token.hpp" // TO_DEL
#include <sstream> // TO_DEL
#include <string> // TO_DEL

bool isOperation(std::string& c)
{
  return ((c == "+") || (c == "-") || (c == "/") || (c == "*") || (c == "%"));
}

bool isBracket(std::string& c)
{
  return ((c == "(") || (c == ")"));
}

int precedence(char c)
{
  if (c == '+' || c == '-')
  {
    return 1;
  }
  if (c == '*' || c == '%' || c == '/')
  {
    return 2;
  }
  if (c == '(' || c == ')')
  {
    return 0;
  }
  return -1;
}

strelyaev::Queue< strelyaev::ExpressionUnit > makeQueue(std::istream& in)
{
  strelyaev::Queue< strelyaev::ExpressionUnit > token_queue;
  std::string str = "";
  while (in >> str)
  {
    strelyaev::TokenType type = strelyaev::TokenType::NONE;
    strelyaev::Token new_token;
    char ch = 0;
    if (isOperation(str))
    {
      ch = str[0];
      new_token = strelyaev::Token(ch);
      type = strelyaev::TokenType::OPERATION;
    }
    else if (isBracket(str))
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

void printQueue(strelyaev::Queue< strelyaev::ExpressionUnit > queue)
{
  while (!queue.empty())
  {
    strelyaev::ExpressionUnit a = queue.drop();
    switch (a.type)
    {
    case strelyaev::TokenType::BRACKET:
      std::cout << a.token.operation << " ";
      break;
    case strelyaev::TokenType::OPERATION:
      std::cout << a.token.operation << " ";
      break;
    case strelyaev::TokenType::OPERAND:
      std::cout << a.token.operand << " ";
      break;
    default:
      std::cerr << "Something went wrong\n";
      break;
    }
  }
}

strelyaev::Queue< strelyaev::ExpressionUnit > makePostfix(strelyaev::Queue< strelyaev::ExpressionUnit > queue)
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
      if (precedence(unit.token.operation) > precedence(stack_peek.token.operation))
      {
        temp_stack.push(stack_peek);
        temp_stack.push(unit);
      }
      else if (precedence(unit.token.operation) <= precedence(stack_peek.token.operation))
      {
        while (precedence(unit.token.operation) <= precedence(stack_peek.token.operation))
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

int main(int argc, char * argv[])
{
  using namespace strelyaev;
  std::fstream input(argv[1]);
  Queue< ExpressionUnit > infix_units_queue = makeQueue(input);
  Queue< ExpressionUnit > postfix_units_queue = makePostfix(infix_units_queue);
  printQueue(postfix_units_queue);
}
