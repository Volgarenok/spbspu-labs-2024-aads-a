#ifndef GET_POSTFIX_FROM_INFIX_HPP
#define GET_POSTFIX_FROM_INFIX_HPP
#include <iostream>
#include <string>
#include "queue.hpp"

namespace zakozhurnikova
{
  void getPostfixFromInfix(std::istream &in, zakozhurnikova::Queue< std::string >& queue);
}
#endif
