#ifndef INPUTINFIX_HPP
#define INPUTINFIX_HPP

#include <iosfwd>
#include <string>
#include "queue.hpp"

namespace isaychev
{
  void inputInfix(std::istream & in, std::string & str, Queue< std::string > & infExp);
}

#endif
