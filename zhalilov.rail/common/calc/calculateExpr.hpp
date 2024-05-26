#ifndef CALCULATEEXPR_HPP
#define CALCULATEEXPR_HPP

#include <queue.hpp>

namespace zhalilov
{
  struct PostfixToken;
  long long calculateExpr(Queue< PostfixToken > expr);
  long long calculateExpr(List< PostfixToken > expr);
}

#endif
