#include "commands.hpp"

#include <iostream>

#include <calc/calculateExpr.hpp>
#include <calc/getInfix.hpp>
#include <calc/infixToPostfix.hpp>

namespace zhalilov
{
  void replaceVars(const modulesMap &modules, List< InfixToken > &oldInf, List< InfixToken > &newInf);
}

void zhalilov::calc(const modulesMap &modules, std::ostream &historyFile, std::istream &in, std::ostream &out)
{
  List< InfixToken > infix;
  getInfix(infix, in);
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }

  List< InfixToken > infWithReplacedVars;
  replaceVars(modules, infix, infWithReplacedVars);
  List< PostfixToken > postfix;
  infixToPostfix(infWithReplacedVars, postfix);
  out << calculateExpr(postfix);
}

void zhalilov::modulesadd(modulesMap &modules, std::istream &in, std::ostream &out)
{
  std::string moduleName;
  in >> moduleName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }

  auto insertPair = modules.insert(std::make_pair(moduleName, varModule{}));
  if (!insertPair.second)
  {
    throw std::invalid_argument("module already exists");
  }
}

void zhalilov::modulesvarradd(modulesMap &modules, std::istream &in, std::ostream &out)
{
  std::string moduleName;
  std::string varName;
  in >> varName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }

  auto moduleIt = modules.find(moduleName);
  if (moduleIt != modules.end())
  {
    List< InfixToken > infix;
    getInfix(infix, in);
    auto varIt = moduleIt->second.find(varName);
    if (varIt != moduleIt->second.end())
    {
      varIt->second = infix;
    }
    else
    {
      moduleIt->second.insert(std::make_pair(varName, infix));
    }
  }
  else
  {
    throw std::invalid_argument("module doesn't exist");
  }
}

void zhalilov::modulesshow(const modulesMap &modules, std::istream &in, std::ostream &out)
{
  std::string checkStream;
  in >> checkStream;
  if (in)
  {
    throw std::invalid_argument("too many args");
  }
  in.clear();
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
