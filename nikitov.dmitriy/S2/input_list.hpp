#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <list.hpp>
#include "queue.hpp"
#include "expression_type.hpp"

namespace nikitov
{
  void inputList(List< Queue< InfixType > >& expressionList, std::istream& input);
}
#endif
