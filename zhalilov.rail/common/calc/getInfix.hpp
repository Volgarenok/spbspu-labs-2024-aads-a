#ifndef GETINFIX_HPP
#define GETINFIX_HPP

#include <iosfwd>

#include <queue.hpp>

#include "expressionTokens.hpp"

namespace zhalilov
{
  void getInfix(Queue< InfixToken > &queue, std::istream &in);
  void getInfix(List< InfixToken > &list, std::istream &in);
}

#endif
