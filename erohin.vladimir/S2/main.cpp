#include <iostream>
#include <sstream>
#include <stdexcept>
#include "token.hpp"
#include "infix_expression.hpp"
#include <queue>

int main()
{
  using namespace erohin;
  std::string string_token;
  std::istringstream input("23 - ( 98 * ( 9 - 2 ) )");
  InfixExpression input_queue;
  inputInfixExpression(input, input_queue);
  Operator oper('+');
  Operand res = oper.evaluate(Operand(2), Operand(3));
  std::cout << res();
}
