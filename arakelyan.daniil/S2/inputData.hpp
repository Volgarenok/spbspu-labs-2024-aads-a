#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iosfwd>
#include "queue.hpp"
#include "expressionObject.hpp"

namespace arakelyan
{
  Queue< detail::ExpressionObj > readDataInInfixForm(std::istream &input);
}
#endif
