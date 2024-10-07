#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include "queue.hpp"

namespace chistyakov
{
  bool prioritet(std::string fstOp, std::string sndOp);
  void infixToPostfix(Queue< std::string > & queue, Queue< std::string > & exp);
}

#endif
