#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <istream>
#include "queue.hpp"
#include "stack.hpp"

namespace chistyakov
{
  void inputExp(Stack< Queue< std::string > > & result, std::istream & in);
}

#endif
