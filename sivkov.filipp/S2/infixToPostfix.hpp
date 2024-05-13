#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include <queue.hpp>

namespace sivkov
{
  Queue< std::string > infixToPostfix(Queue< std::string >& infix);
}

#endif
