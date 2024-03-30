#ifndef GETINFIXFROMSTRING_HPP
#define GETINFIXFROMSTRING_HPP

#include <iosfwd>

#include "queue.hpp"
#include "expressionTokens.hpp"

namespace zhalilov
{
  void getInfixFromString(Queue< InfixToken > &queue, const std::string &in);
}

#endif
