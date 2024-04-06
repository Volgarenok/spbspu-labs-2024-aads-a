#include <iostream>
#include "queue.hpp"
#include "token.hpp" // TO_DEL
#include <sstream> // TO_DEL
#include <string> // TO_DEL
#include "stack.hpp"

bool isOperation(std::string& c)
{
  return ((c == "+") || (c == "-") || (c == "/") || (c == "*") || (c == "%"));
}

bool isBracket(std::string& c)
{
  return ((c == "(") || (c == ")"));
}

strelyaev::Queue< strelyaev::infixUnit > makeQueue(std::istream& in)
{
  strelyaev::Queue< strelyaev::infixUnit > token_queue;
  std::string str = "";
  while (in >> str)
  {
    strelyaev::typeOfExpression type = strelyaev::typeOfExpression::NONE;
    strelyaev::Token new_token;
    char ch = 0;
    if (isOperation(str))
    {
      ch = str[0];
      new_token = strelyaev::Token(ch);
      type = strelyaev::typeOfExpression::OPERATION;
    }
    else if (isBracket(str))
    {
      ch = str[0];
      new_token = strelyaev::Token(ch);
      type = strelyaev::typeOfExpression::BRACKET;
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
      type = strelyaev::typeOfExpression::OPERAND;
    }
    strelyaev::infixUnit new_unit{new_token, type};
    token_queue.push(new_unit);
  }
  return token_queue;
}

void printQueue(strelyaev::Queue< strelyaev::infixUnit > queue)
{
  while (!queue.empty())
  {
    strelyaev::infixUnit a = queue.drop();
    switch (a.type)
    {
    case strelyaev::typeOfExpression::BRACKET:
      std::cout << "{" << a.token.operation << "}\n";
      break;
    case strelyaev::typeOfExpression::OPERATION:
      std::cout << "{" << a.token.operation <<"}\n";
      break;
    case strelyaev::typeOfExpression::OPERAND:
      std::cout << "{" << a.token.operand << "}\n";
      break;
    default:
      std::cerr << "Something went wrong\n";
      break;
    }
  }
}

int main()
{
  using namespace strelyaev;
  std::string infix = "( -2 + 3 ) / 5";
  std::stringstream ss(infix);
  Queue< infixUnit > infix_units_queue = makeQueue(ss);
  printQueue(infix_units_queue);
}
