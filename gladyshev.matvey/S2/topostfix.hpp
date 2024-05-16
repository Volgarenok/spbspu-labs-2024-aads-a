#ifndef TOPOSTFIX_HPP
#define TOPOSTFIX_HPP

#include <string>

#include "queue.hpp"

namespace gladyshev
{
  Queue< std::string > infixToPostfix(Queue< std::string >& expression);
}

#endif
