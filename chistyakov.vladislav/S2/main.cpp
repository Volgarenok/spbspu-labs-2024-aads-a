#include <iostream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "infixToPostfix.hpp"
#include "input.hpp"
#include "calculate.hpp"

int main()
{
  using namespace chistyakov;

  Queue< std::string > exp;
  std::string a = "5*6+(2-9)";
  std::cout << a << "\n";

  inputExp(exp, a);
  Queue< std::string > result;
  infixToPostfix(result, exp);
  int resultNum = calculate(result);

  std::cout << "Result: " << resultNum << "\n";
}
