#ifndef INPUT_INFIX_HPP
#define INPUT_INFIX_HPP

#include <istream>
#include <string>
#include <queue.hpp>
#include "tokens.hpp"

namespace novokhatskiy
{
  void inputInfix(Queue< Queue< InfixType > >& infixQueue, std::istream& in);
}

#endif
