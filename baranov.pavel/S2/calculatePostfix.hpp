#ifndef CALCULATE_POSTFIX_HPP
#define CALCULATE_POSTFIX_HPP

#include "tokens.hpp"
#include <queue.hpp>
#include <stack.hpp>

namespace baranov
{
  void calculatePostfixes(Queue< Queue< Token > > & postfixes, Stack< long long int > & result);
  long long int calculatePostfix(Queue< Token > &);
  long long int sum(long long int a, long long int b);
  long long int multiply(long long int a, long long int b);
  long long int div(long long int a, long long int b);
  long long int mod(long long int a, long long int b);
  int sign(long long int val);
  bool same_sign(long long int a, long long int b);
}

#endif

