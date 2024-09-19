#ifndef INPUT_POSTFIX_HPP
#define INPUT_POSTFIX_HPP

#include <istream>
#include <queue.hpp>
#include "tokens.hpp"

namespace baranov
{
  void inputPostfixes(std::istream &, Queue< Queue< Token > > & result);
  void inputPostfix(std::istream &, Queue< Token > & result);
}

#endif

