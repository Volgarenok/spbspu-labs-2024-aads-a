#ifndef TYPES_HPP
#define TYPES_HPP
#include "partexpression.hpp"

namespace piyavkin
{
  struct InputType
  {
    union input_t
    {
      detail::Operand operand;
      detail::Operation operation;
      detail::Bracket bracket;      
    };
    input_t symbol;
    detail::TypesPartsExpression type;
  };
}
#endif