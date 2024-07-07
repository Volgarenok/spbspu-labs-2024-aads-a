#ifndef CALCULATE_POSTFIX_HPP
#define CALCULATE_POSTFIX_HPP

#include "tokens.hpp"
#include "queue.hpp"

namespace baranov
{
  long long int calculatePostfix(Queue< Token > &);
  long long int sum(long long int a, long long int b);
  int sign(long long int val);
  bool same_sign(long long int a, long long int b);
}

#endif

