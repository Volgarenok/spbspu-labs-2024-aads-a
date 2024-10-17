#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP

#include <string>
#include "queue.hpp"

namespace petuhov {
  petuhov::Queue< std::string > infixToPostfix(const std::string &expression);
}

#endif
