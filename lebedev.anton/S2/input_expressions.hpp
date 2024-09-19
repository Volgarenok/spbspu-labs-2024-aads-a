#ifndef INPUT_EXPRESSIONS_HPP
#define INPUT_EXPRESSIONS_HPP

#include <istream>
#include "expression_types.hpp"
#include "queue.hpp"

namespace lebedev
{
  void inputInfixExpression(Queue< Queue< InfixExpression > > & queueInfix, std::istream & input);
}

#endif
