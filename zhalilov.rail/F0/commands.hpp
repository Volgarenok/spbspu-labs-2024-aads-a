#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>

#include <calc/expressionTokens.hpp>
#include <tree/twoThreeTree.hpp>
#include <list/list.hpp>

namespace zhalilov
{
  using varModule = TwoThree< std::string, List< InfixToken > >;
  using modulesMap = TwoThree< std::string, varModule >;
  void calc(const modulesMap &, std::ostream &, std::istream &, std::ostream &);
}

#endif
