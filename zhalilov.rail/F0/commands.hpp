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
  void calc(const modulesMap &, const std::string &, std::istream &, std::ostream &);
  void modulesadd(modulesMap &, std::istream &, std::ostream &);
  void modulesvaradd(modulesMap &, std::istream &, std::ostream &);

  void modulesdelete(modulesMap &, std::istream &, std::ostream &);
  void modulesvardelete(modulesMap &, std::istream &, std::ostream &);

  void modulesshow(const modulesMap &, std::istream &, std::ostream &);

  void modulesimport(modulesMap &, std::istream &, std::ostream &);
  void modulesexport(const modulesMap &, std::istream &, std::ostream &);

  void historyshow(const std::string &, std::istream &, std::ostream &);
  void historyclear(const std::string &, std::istream &, std::ostream &);
}

#endif
