#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "postfix_expression.hpp"
#include "stack.hpp"

int main(int argc, char** argv)
{
  std::ifstream finput;
  if (argc == 2)
  {
    finput.open(argv[1]);
  }
  std::istream& input = (argc == 2 ? finput : std::cin);
  using namespace zaitsev;
  try
  {
    Stack< long long >results;
    while (input)
    {
      std::string s;
      std::getline(input, s);
      if (s == "" || !input)
      {
        continue;
      }
      PostfixExpression expr(s);
      results.push(expr.calculate());
    }
    if (!results.empty())
    {
      std::cout << results.top();
      results.pop();
    }
    while(!results.empty())
    {
      std::cout << ' ' << results.top();
      results.pop();
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
