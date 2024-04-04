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
    if (isOperation(str))
    {
      char ch = str[0];
      strelyaev::Token new_token(ch);
      strelyaev::infixUnit new_unit{new_token, strelyaev::typeOfExpression::OPERATION};
      token_queue.push(new_unit);
      std::cout << "{" << new_unit.token.operation.operation << "}\n";
      continue;
    }
    if (isBracket(str))
    {
      char ch = str[0];
      strelyaev::Token new_token(ch);
      strelyaev::infixUnit new_unit{new_token, strelyaev::typeOfExpression::BRACKET};
      token_queue.push(new_unit);
      std::cout << "{" << new_unit.token.bracket.bracket << "}\n";
      continue;
    }
    long long operand = 0;
    try
    {
      operand = std::stoll(str);
    }
    catch (const std::exception& e)
    {
      continue;
    }
    strelyaev::Token new_token(operand);
    strelyaev::infixUnit new_unit{new_token, strelyaev::typeOfExpression::OPERAND};
    token_queue.push(new_unit);
    std::cout << "{" << new_unit.token.operand.operand << "}\n";
  }
  return token_queue;
}

int main()
{
  using namespace strelyaev;
  std::string infix = "( 12 + 14 ) / 7";
  std::stringstream ss(infix);
  Queue< infixUnit > infix_units_queue = makeQueue(ss);
}
