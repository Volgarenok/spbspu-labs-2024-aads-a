#ifndef CONVERTINFTOPOSTF_HPP
#define CONVERTINFTOPOSTF_HPP

#include <string>
#include "stack.hpp"
#include "queue.hpp"

namespace isaychev
{
  void convertInfToPostf(Queue< std::string > & infExp, Queue< std::string > & postfExp);
}

#endif
