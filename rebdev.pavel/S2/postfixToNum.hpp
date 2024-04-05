#ifndef POSTFIXTONUM_HPP
#define POSTFIXTONUM_HPP

#include "myQueue.hpp"
#include "node.hpp"

namespace rebdev
{
  long long convertPostfixToNum(Queue< node > & postfixQueue);
}

#endif
