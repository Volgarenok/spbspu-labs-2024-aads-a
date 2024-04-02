#ifndef INPUT_EXPRESSIONS_HPP
#define INPUT_EXPRESSIONS_HPP

#include <stack>
#include <queue>
#include <string>
#include <iostream>

namespace namestnikov
{
  void inputExpressions(std::istream & in, std::stack< std::queue< std::string > > & expressionsStack);
  void inputExpression(std::string s, std::queue< std::string > & expression);
}

#endif