#include <calc/varExpression.hpp>

zhalilov::VarExpression::VarExpression():
  args_{}
{}

zhalilov::VarExpression::VarExpression(const std::string &module, const std::string &var, const List< long long > &args):
  moduleName_{ module },
  varName_{ var },
  args_{ args }
{}

std::string zhalilov::VarExpression::getModuleName()
{
  return moduleName_;
}

std::string zhalilov::VarExpression::gerVarName()
{
  return varName_;
}

zhalilov::List< long long > zhalilov::VarExpression::getArgs()
{
  return args_;
}
