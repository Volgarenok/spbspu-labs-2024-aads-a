#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"

namespace arakelyan
{
  Queue< ExpressionObj > readDataInInfixForm(std::istream &input);
}
#endif
