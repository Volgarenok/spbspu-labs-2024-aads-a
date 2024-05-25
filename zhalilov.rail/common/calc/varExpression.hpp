#ifndef VAREXPRESSION_HPP
#define VAREXPRESSION_HPP

#include <string>

#include <list/list.hpp>

namespace zhalilov
{
  class VarExpression
  {
  public:
    VarExpression();
    VarExpression(const std::string &, const std::string &, const List< long long > &);
    std::string getModuleName();
    std::string gerVarName();
    List < long long > getArgs();

  private:
    std::string moduleName_;
    std::string varName_;
    List< long long > args_;
  };
}

#endif
