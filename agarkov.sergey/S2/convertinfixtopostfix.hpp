#ifndef CONVERINFIXTOPOSTFIX_HPP
#define CONVERINFIXTOPOSTFIX_HPP
#include <string>
#include "queue.hpp"

namespace agarkov
{
  Queue< std::string > convertInfixToPostfix(Queue< std::string >& infixQueue);
}

#endif
