#include "commands.hpp"

#include <iostream>

#include <calc/calculateExpr.hpp>
#include <calc/getInfix.hpp>
#include <calc/infixToPostfix.hpp>

namespace zhalilov
{
  InfixToken replaceVars(const modulesMap &modules, InfixToken infToReplace);
  void outputInfix(List< InfixToken > infix, std::ostream &out);
  std::ostream &operator<<(std::ostream &out, const Operand &op);
  std::ostream &operator<<(std::ostream &out, const Bracket &br);
  std::ostream &operator<<(std::ostream &out, const BinOperator &binOp);
  std::ostream &operator<<(std::ostream &out, const VarExpression &varExpr);
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
  for (auto it = infix.begin(); it != infix.end(); ++it)
  {
    if (it->getType() == PrimaryType::VarExpression)
    {
      infWithReplacedVars.push_back(replaceVars(modules, *it));
    }
    else
    {
      infWithReplacedVars.push_back(*it);
    }
  }
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
  in >> moduleName >> varName;
  if (!in)
  {
    throw std::invalid_argument("bad input");
  }

  auto moduleIt = modules.find(moduleName);
  if (moduleIt != modules.end())
  {
    List< InfixToken > infix;
    getInfix(infix, in);
    if (infix.empty())
    {
      throw std::invalid_argument("not enough args");
    }
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
  std::getline(in, checkStream);
  if (!checkStream.empty())
  {
    throw std::invalid_argument("too many args");
  }

  for (auto it = modules.cbegin(); it != modules.cend(); ++it)
  {
    out << it->first << ":\n";
    for (auto inModuleIt = it->second.cbegin(); inModuleIt != it->second.cend(); ++inModuleIt)
    {
      out << inModuleIt->first << " =";
      outputInfix(inModuleIt->second, out);
      out << '\n';
    }
  }
}

zhalilov::InfixToken zhalilov::replaceVars(const modulesMap &modules, InfixToken infToReplace)
{
  std::string moduleName = infToReplace.getVarExpression().getModuleName();
  std::string varName = infToReplace.getVarExpression().gerVarName();
  varModule module = modules.at(moduleName);
  List< InfixToken > varList = module.at(varName);
  List< InfixToken > replaced;
  List< long long > args = infToReplace.getVarExpression().getArgs();
  for (auto exprIt = varList.cbegin(); exprIt != varList.cend(); ++exprIt)
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
  return InfixToken(Operand(calculated));
}

void zhalilov::outputInfix(List< InfixToken > infix, std::ostream &out)
{
  for (auto it = infix.begin(); it != infix.end(); ++it)
  {
    switch (it->getType())
    {
    case PrimaryType::Operand:
      out << ' ' << it->getOperand();
      return;
    case PrimaryType::BinOperator:
      out << ' ' << it->getBinOperator();
      return;
    case PrimaryType::VarExpression:
      out << ' ' << it->getVarExpression();
      return;
    default:
      out << ' ' << it->getBracket();
      return;
    }
  }
}

std::ostream &zhalilov::operator<<(std::ostream &out, const Operand &op)
{
  return out << op.getNum();
}

std::ostream &zhalilov::operator<<(std::ostream &out, const Bracket &br)
{
  if (br.getType() == PrimaryType::CloseBracket)
  {
    return out << '(';
  }
  return out << ')';
}

std::ostream &zhalilov::operator<<(std::ostream &out, const BinOperator &binOp)
{
  switch (binOp.getType())
  {
  case BinOperator::Type::Addition:
    return out << '+';
  case BinOperator::Type::Subtraction:
    return out << '-';
  case BinOperator::Type::Multiplication:
    return out << '*';
  case BinOperator::Type::Division:
    return out << '/';
  case BinOperator::Type::Mod:
    return out << '%';
  default:
    return out;
  }
}

std::ostream &zhalilov::operator<<(std::ostream &out, const VarExpression &varExpr)
{
  out << varExpr.getModuleName() << ':' << varExpr.gerVarName();
  List< long long > args = varExpr.getArgs();
  if (!args.empty())
  {
    auto it = args.cbegin();
    out << '(' << *it;
    ++it;
    for (; it != args.cend(); ++it)
    {
      out << ", " << *it;
    }
    out << ')';
  }
  return out;
}
