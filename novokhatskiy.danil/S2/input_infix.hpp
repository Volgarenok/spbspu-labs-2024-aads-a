#ifndef INPUT_INFIX_HPP
#define INPUT_INFIX_HPP

#include <string>
#include <istream>
#include "tokens.hpp"
#include "queue.hpp"

namespace novokhatskiy
{
  InfixType checkType(std::string& str);
  void inputInfix(Queue< Queue< InfixType > > infixQueue, std::istream& in);
}

#endif
