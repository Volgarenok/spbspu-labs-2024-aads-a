#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"

namespace arakelyan
{
  void readDataInfixForm(std::istream &input, Queue< ExpressionObj > &someQ);
}
#endif
