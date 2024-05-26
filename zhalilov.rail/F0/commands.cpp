#include "commands.hpp"

#include <calc/calculateExpr.hpp>
#include <calc/getInfix.hpp>
#include <calc/infixToPostfix.hpp>
#include <listQueueCasting.hpp>

namespace zhalilov
{
  void replaceVars(const modulesMap &modules, List< InfixToken > &oldInf, List< InfixToken > &newInf);
}

void zhalilov::calc(const modulesMap &modules, std::ostream &historyFile, std::istream &in, std::ostream &out)
{
  List< InfixToken > infix;
  getInfix(infix, in);
  List< InfixToken > infWithReplacedVars;
  replaceVars(modules, infix, infWithReplacedVars);
}

void zhalilov::modulesadd(modulesMap &modules, std::istream &in, std::ostream &out)
{
  std::string moduleName;
  in >> moduleName;
  auto insertPair = modules.insert(std::make_pair(moduleName, varModule{}));
  if (!insertPair.second)
  {
    throw std::invalid_argument("module already exists");
  }
}

void zhalilov::replaceVars(const modulesMap &modules, List< InfixToken > &oldInf, List< InfixToken > &newInf)
{
  for (auto it = oldInf.begin(); it != oldInf.end(); ++it)
  {
    if (it->getType() == PrimaryType::VarExpression)
    {
      std::string moduleName = it->getVarExpression().getModuleName();
      std::string varName = it->getVarExpression().gerVarName();
      varModule module = modules.at(moduleName);
      List< InfixToken > varList = module.at(varName);
      List< InfixToken > replaced;
      List< long long > args = it->getVarExpression().getArgs();
      for (auto exprIt = varList.cbegin(); exprIt != varList.cend(); ++it)
      {
        if (exprIt->getType() == PrimaryType::VarExpression)
        {
          if (args.empty())
          {
            throw std::invalid_argument("not enough args");
          }
          replaced.push_back(InfixToken(Operand(args.front())));
          args.pop_front();
        }
        replaced.push_back(*exprIt);
      }
      List< PostfixToken > postfixReplaced;
      infixToPostfix(replaced, postfixReplaced);
      long long calculated = calculateExpr(postfixReplaced);
      newInf.push_back(InfixToken(Operand(calculated)));
    }
    else
    {
      newInf.push_back(*it);
    }
  }
}
