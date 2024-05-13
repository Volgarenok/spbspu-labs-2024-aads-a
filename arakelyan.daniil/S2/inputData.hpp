#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iosfwd>
#include "queue.hpp"
#include "expressionObject.hpp"

namespace arakelyan
{
  std::istream &readDataInInfixFormat(std::istream &input, Queue< Queue< ExpressionObj > > & qOfInfixQs);
}
#endif
