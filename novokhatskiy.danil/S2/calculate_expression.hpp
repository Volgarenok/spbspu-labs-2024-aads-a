#ifndef CALCULATE_EXPRESSION_HPP
#define CALCULATE_EXPRESSION_HPP

#include "queue.hpp"
#include "tokens.hpp"

namespace novokhatskiy
{
  long long calculateExp(long long& val1, long long& val2, char oper);
  long long calculatePostExp(Queue< Postfix >& postQ);
}

#endif
