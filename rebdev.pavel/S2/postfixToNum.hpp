#ifndef POSTFIXTONUM_HPP
#define POSTFIXTONUM_HPP

#include "myQueue.hpp"
#include "node.hpp"

namespace rebdev
{
  long long convertPostfixToNum(queue< node > & postfixQueue);
}

#endif
