#ifndef CALCULATIONS_HPP
#define CALCULATIONS_HPP
#include <string>
#include <iosfwd>
#include "token.hpp"
#include <others/queue.hpp>
namespace strelyaev
{
  long long calculateOperation(const ExpressionUnit&, const ExpressionUnit&, const ExpressionUnit&);
}
#endif


