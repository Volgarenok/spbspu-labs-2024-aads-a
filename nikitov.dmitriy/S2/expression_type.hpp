#ifndef EXPRESSION_TYPE_HPP
#define EXPRESSION_TYPE_HPP

#include <cstddef>

namespace nikitov
{
  struct ExpressionType
  {
    union ExpressionValue
    {
      char symb;
      int num;
    } value;

    size_t storedType;
  };
}
#endif
