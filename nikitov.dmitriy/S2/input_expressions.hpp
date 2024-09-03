#ifndef INPUT_EXPRESSIONS_HPP
#define INPUT_EXPRESSIONS_HPP

#include <istream>
#include <queue.hpp>
#include "infix_type.hpp"

namespace nikitov
{
  void inputExpressions(Queue< Queue< InfixType > >& infixQueue, std::istream& input);
}
#endif
