#ifndef CONVERTPOSTFIX_HPP
#define CONVERTPOSTFIX_HPP
#include "queue.hpp"
#include "types.hpp"

namespace piyavkin
{
  using infix_t = List< Queue< InputType > >;
  using postfix_t = List< Queue< Postfix > >;
  void convertPostfix(infix_t& infix, postfix_t& postfix);
}
#endif
