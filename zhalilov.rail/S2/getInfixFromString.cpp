#include "getInfixFromString.hpp"

#include <string>

void zhalilov::getInfixFromString(Queue< InfixToken > &queue, const std::string &str)
{
  size_t i = 0;
  size_t tmp = 0;
  long long number = 0;
  while (i != str.size())
  {
    if (!std::isspace(str[i]))
    {
      InfixToken undefinedTkn;
      switch (str[i])
      {
      case '(':
        undefinedTkn = InfixToken(PrimaryType::Bracket);
        undefinedTkn.bracket = Bracket(Bracket::Type::OpenBracket);
        break;
      case ')':
        undefinedTkn = InfixToken(PrimaryType::Bracket);
        undefinedTkn.bracket = Bracket(Bracket::Type::CloseBracket);
        break;
      case '+':
        undefinedTkn = InfixToken(PrimaryType::BinOperator);
        undefinedTkn.binOperator = BinOperator(BinOperator::Type::Add);
        break;
      case '-':
        undefinedTkn = InfixToken(PrimaryType::BinOperator);
        undefinedTkn.binOperator = BinOperator(BinOperator::Type::Subtraction);
        break;
      case '*':
        undefinedTkn = InfixToken(PrimaryType::BinOperator);
        undefinedTkn.binOperator = BinOperator(BinOperator::Type::Multiply);
        break;
      case '/':
        undefinedTkn = InfixToken(PrimaryType::BinOperator);
        undefinedTkn.binOperator = BinOperator(BinOperator::Type::Division);
        break;
      case '%':
        undefinedTkn = InfixToken(PrimaryType::BinOperator);
        undefinedTkn.binOperator = BinOperator(BinOperator::Type::Mod);
        break;
      }
      if (undefinedTkn.getType() == PrimaryType::Undefined)
      {
        number = std::stoll(str.substr(i), &tmp);
        undefinedTkn = InfixToken(PrimaryType::Operand);
        undefinedTkn.operand = Operand(number);
        i += tmp;
      }
      queue.push(undefinedTkn);
    }
    i++;
  }
}
