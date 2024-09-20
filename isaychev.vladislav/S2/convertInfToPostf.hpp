#ifndef CONVERTINFTOPOSTF_HPP
#define CONVERTINFTOPOSTF_HPP

#include <stack.hpp>
#include <queue.hpp>
#include "tokens.hpp"

namespace isaychev
{
  void convertInfToPostf(Queue< Token > & infExp, Queue< Token > & postfExp);
}

#endif
