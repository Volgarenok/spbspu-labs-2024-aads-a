#include <iostream>
#include <sstream>
#include <stdexcept>
#include "token.hpp"
#include "infix_expression.hpp"
#include "postfix_expression.hpp"

#include <queue>
#include <stack>

int main()
{
  using namespace erohin;
  std::string string_token;
  std::cout << "Check!" << std::endl;
  std::istringstream input("0");
  std::queue< Token > input_queue;
  inputInfixExpression(input, input_queue);
  PostfixExpression expr(input_queue);
  Operator oper('+');
  Operand res = oper.evaluate(Operand(2), Operand(3));
  std::cout << res();
}
