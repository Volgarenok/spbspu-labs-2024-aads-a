#include <calc/getInfix.hpp>

#include <string>
#include <istream>

namespace zhalilov
{
  bool isBracket(char symb)
  {
    if (symb == '(' || symb == ')')
    {
      return true;
    }
    return false;
  }

  bool isBinaryOp(char symb)
  {
    bool isOp = symb == '+' || symb == '-';
    isOp = isOp || symb == '/' || symb == '*';
    isOp = isOp || symb == '%';
    return isOp;
  }

  size_t processVarExpr(const std::string &toProcess, VarExpression &varExpr)
  {
    std::string moduleName = "main";
    size_t i = 0;
    while (std::isalpha(toProcess[i]))
    {
      i++;
    }
    if (i != 0)
    {
      std::string varName;
      if (toProcess[i] == ':')
      {
        moduleName = toProcess.substr(0, i);
        size_t nameStartPos = i;
        while (std::isalpha(toProcess[nameStartPos]))
        {
          nameStartPos++;
        }
        if (nameStartPos != i)
        {
          varName = toProcess.substr(nameStartPos, i - nameStartPos);
        }
      }
      else
      {
        varName = toProcess.substr(0, i);
      }
      if (toProcess[i] == '(')
      {
        List< long long > args;
        i++;
        while (toProcess[i] != ')')
        {
          if (toProcess.size() == i)
          {
            throw std::invalid_argument("getInfix.cpp: toProcess.size() == i");
          }
          if (toProcess[i] != ',')
          {
            size_t tmp = 0;
            args.push_back(std::stoll(toProcess.substr(i), &tmp));
            i += tmp;
          }
          else
          {
            i++;
          }
        }
        varExpr = VarExpression(moduleName, varName, args);
      }
    }
    return i;
  }
}

void zhalilov::getInfix(Queue< InfixToken > &queue, std::istream &in)
{
  std::string str;
  std::getline(in, str);
  size_t i = 0;
  size_t tmp = 0;
  long long number = 0;
  while (i < str.size())
  {
    if (!std::isspace(str[i]))
    {
      InfixToken undefinedTkn;
      try
      {
        number = std::stoll(str.substr(i), &tmp);
        undefinedTkn = InfixToken(Operand(number));
        i += tmp;
      }
      catch (...)
      {
        if (isBracket(str[i]))
        {
          undefinedTkn = InfixToken(Bracket(str[i]));
        }
        else if (isBinaryOp(str[i]))
        {
          undefinedTkn = InfixToken(BinOperator(str[i]));
        }
        else
        {
          VarExpression varExpr;
          i = processVarExpr(str.substr(i), varExpr);
          undefinedTkn = InfixToken(varExpr);
        }
      }
      queue.push(undefinedTkn);
    }
    i++;
  }
}
