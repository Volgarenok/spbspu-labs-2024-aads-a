#ifndef INPUT_EXPRESSIONS_HPP
#define INPUT_EXPRESSIONS_HPP

#include <stack>
#include <queue>
#include <string>
#include <iostream>
#include "stack.hpp"
#include "queue.hpp"

namespace namestnikov
{
  void inputExpressions(std::istream & in, Stack< Queue< std::string > > & expressionsStack);
  void inputExpression(std::string s, Queue< std::string > & expression);
}

#endif
