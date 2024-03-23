#ifndef EXPRESSION_TYPE_HPP
#define EXPRESSION_TYPE_HPP

#include <cstddef>

namespace nikitov
{
  struct ExpressionType
  {
    bool operator<(const ExpressionType& other) const;

    union ExpressionValue
    {
      char symb;
      long long int num;
    } value;

    size_t storedType;
  };
}
#endif
