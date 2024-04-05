#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include "tokens.hpp"
#include "inputPostfix.hpp"

int main()
{
  using namespace baranov;
  Queue< Token > postfixExp;
  inputPostfix(std::cin, postfixExp);

  while(!postfixExp.empty())
  {
    Token token = postfixExp.front();
    postfixExp.pop();
    if (token.type == TokenType::OPERAND)
    {
      std::cout << "operand: " << token.value.operand.value << '\n';
    }
    if (token.type == TokenType::OPERATION)
    {
      std::cout << "operation" << '\n';
    }
    if (token.type == TokenType::BRACKET)
    {
      std::cout << "bracket" << '\n';
    }
  }
}

