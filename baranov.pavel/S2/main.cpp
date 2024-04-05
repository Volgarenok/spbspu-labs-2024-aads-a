#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include "tokens.hpp"

int main()
{
  using namespace baranov;
  std::string str = "";
  std::cin >> str;
  Token token(str);
  if (token.type == TokenType::OPERAND)
  {
    std::cout << "operand: " << token.value.operand.value;
  }
  if (token.type == TokenType::OPERATION)
  {
    std::cout << "operation";
  }
  if (token.type == TokenType::BRACKET)
  {
    std::cout << "bracket";
  }
}

