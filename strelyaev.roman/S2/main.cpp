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

strelyaev::Queue< strelyaev::ExpressionUnit > makeQueue(std::istream& input)
{
  std::string temp_string = "";
  std::getline(input, temp_string);
  std::istringstream in(temp_string);
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

strelyaev::Queue< strelyaev::ExpressionUnit > makePostfix(strelyaev::Queue< strelyaev::ExpressionUnit >& queue)
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

long long calculateOperation(long long first, long long second, char operation)
{
  switch (operation)
  {
  case '+':
    return first + second;
  case '-':
    return first - second;
  case '*':
    return first * second;
  case '/':
    return first / second;
  case '%':
    return first % second;
  }
  throw std::logic_error("Invalid operation");
}

long long calculatePostfix(strelyaev::Queue< strelyaev::ExpressionUnit > queue)
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

long long calculateInfixExpression(std::istream& in)
{
  strelyaev::Queue< strelyaev::ExpressionUnit > infix_units_queue = makeQueue(in);
  strelyaev::Queue< strelyaev::ExpressionUnit > postfix_units_queue = makePostfix(infix_units_queue);
  long long result = calculatePostfix(postfix_units_queue);
  return result;
}

void printResults(strelyaev::Stack< long long >& results, std::ostream& out)
{
  while (!results.empty())
  {
    out << results.drop();
    if (!results.empty())
    {
      out << " ";
    }
  }
}

int main(int argc, char * argv[])
{
  using namespace strelyaev;
  Stack< long long > results;
  if (argc == 1)
  {
    while (std::cin.good())
    {
      long long result = 0;
      try
      {
        result = calculateInfixExpression(std::cin);
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
      results.push(result);
    }
    printResults(results, std::cout);
  }
  else if (argc == 3)
  {
    std::ifstream input_file(argv[1]);
    std::ofstream output_file(argv[2]);
    while (input_file.good())
    {
      long long result = 0;
      try
      {
        result = calculateInfixExpression(input_file);
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
      results.push(result);
    }
    printResults(results, output_file);
  }
  else
  {
    std::cerr << "Invalid cmd parameters\n";
    return 1;
  }
}
