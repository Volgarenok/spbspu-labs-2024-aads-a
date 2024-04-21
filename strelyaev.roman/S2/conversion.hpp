#ifndef CONVERSION
#define CONVERSION
#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"
namespace strelyaev
{
  strelyaev::detail::ExpressionUnit convertStringToUnit(std::string);
  strelyaev::Queue< strelyaev::detail::ExpressionUnit > parseString(std::istream&);
  Queue< detail::ExpressionUnit > makePostfix(Queue< detail::ExpressionUnit >&);
  long long calculatePostfix(strelyaev::Queue< strelyaev::detail::ExpressionUnit >&);
}
#endif

