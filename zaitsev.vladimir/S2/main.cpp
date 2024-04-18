#include <iostream>
#include <string>
#include <fstream>
#include "token.hpp"
#include "infix_expression.hpp"
#include "postfix_expression.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "operators.hpp"

int main(int argc, char** argv)
{
  std::ifstream finput;
  if (argc == 2)
  {
    finput.open(argv[1]);
  }
  std::istream& input = argc == 2 ? finput : std::cin;
  using namespace zaitsev;
  try
  {
    Stack< long long >results;
    while (input)
    {
      std::string s;
      std::getline(input, s);
      if (s == "")
      {
        continue;
      }
      InfixExpression< long long > infix_expr(s, std::stoll);
      PostfixExpression< long long > postfix_expr(infix_expr);
      results.push(postfix_expr.calculate());
    }
    for (Stack< long long >::const_iterator i = results.cbegin(); i != results.cend(); ++i)
    {
      i == results.cbegin() ? std::cout << *i : std::cout << ' ' << *i;
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr <<"Error: "<< e.what() << '\n';
    return 1;
  }
  return 0;
}
