#ifndef POSTFIX_FROM_INFIX_HPP
#define POSTFIX_FROM_INFIX_HPP

#include <string>
#include "queue.hpp"

namespace grechishnikov
{
  Queue< std::string > postfixFromInfix(const Queue< std::string >& infix);
}

#endif
