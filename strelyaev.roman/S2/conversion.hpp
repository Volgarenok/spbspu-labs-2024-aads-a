#ifndef CONVERSION
#define CONVERSION
#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"
namespace strelyaev
{
  Queue< ExpressionUnit > makeQueue(std::istream&);
  Queue< ExpressionUnit > makePostfix(Queue< ExpressionUnit >&);
  long long calculatePostfix(strelyaev::Queue< strelyaev::ExpressionUnit >&);
  long long calculateInfixExpression(std::istream& in);
}
#endif
