#ifndef TYPES_HPP
#define TYPES_HPP
#include "partexpression.hpp"

namespace piyavkin
{
  struct InputType
  {
    union InputType
    {
      detail::Operand operand;
      detail::Operation operation;
      detail::Bracket bracket;      
    };
    detail::TypesPartsExpression type;
  };
}
#endif