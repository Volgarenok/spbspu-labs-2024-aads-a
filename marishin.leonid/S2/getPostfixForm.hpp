#ifndef GET_POSTFIX_FORM_HPP
#define GET_POSTFIX_FORM_HPP

#include <iosfwd>
#include <string>
#include "queue.hpp"

namespace marishin
{
  void getPostfixForm(std::istream& in, Queue< std::string >& queue);
}

#endif
