#ifndef GETINFIX_HPP
#define GETINFIX_HPP

#include <iosfwd>

#include "queue.hpp"
#include "expressionTokens.hpp"
#include "stack.hpp"

namespace zhalilov
{
  void getInfixFromString(Queue< InfixToken > &queue, const std::string &in);
  void getInfixesFromStream(Stack< Queue< InfixToken > > &stack, std::istream &in);
}

#endif
