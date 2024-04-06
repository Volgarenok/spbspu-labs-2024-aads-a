#ifndef CONVERSION
#define CONVERSION
#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"
namespace strelyaev
{
  Queue< detail::ExpressionUnit > makeQueue(std::istream&);
  Queue< detail::ExpressionUnit > makePostfix(Queue< detail::ExpressionUnit >&);
  long long calculatePostfix(strelyaev::Queue< strelyaev::detail::ExpressionUnit >&);
  long long calculateInfixExpression(std::istream& in);
}
#endif
