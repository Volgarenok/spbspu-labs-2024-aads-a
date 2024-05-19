#ifndef CONVERSION_HPP
#define CONVERSION_HPP
#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"
namespace strelyaev
{
  strelyaev::ExpressionUnit convertStringToUnit(std::string);
  strelyaev::Queue< strelyaev::ExpressionUnit > parseString(std::istream&);
  Queue< ExpressionUnit > makePostfix(Queue< ExpressionUnit >&);
  long long calculatePostfix(strelyaev::Queue< strelyaev::ExpressionUnit >&);
}
#endif


