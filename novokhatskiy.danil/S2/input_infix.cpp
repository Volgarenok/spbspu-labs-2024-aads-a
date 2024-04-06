#include <string>
#include "input_infix.hpp"

// novokhatskiy::InfixType novokhatskiy::checkType(std::string& str)
//{
//   if (std::isdigit(str[0]))
//   {
//     return InfixType(PartsOfExpression::operand, str[0]);
//   }
//   else if (str[0] == '(')
//   {
//     return InfixType(PartsOfExpression::openBracket, str[0] == '(');
//   }
//   else if (str[0] == ')')
//   {
//     return InfixType(PartsOfExpression::closedBracket, str[0]);
//   }
//   else
//   {
//     return InfixType(PartsOfExpression::operation, str[0]);
//   }
// }

void novokhatskiy::inputInfix(Queue< Queue< InfixType > >& infixQueue, std::istream& in)
{
  in >> std::noskipws;
  while (in)
  {
    char symb{};
    Queue< InfixType > currQ;
    InfixType res;
    while (in >> symb)
    {
      if (symb == ' ')
      {
        continue;
      }
      if (std::isdigit(symb))
      {
        std::string str = {};
        while (symb != ' ' && symb != '\n')
        {
          str += symb;
          in >> symb;
        }
        res.data.operand.value = std::stoll(str);
        res.type = PartsOfExpression::OPERAND;
        if (symb == '\n')
        {
          currQ.push(res);
          break;
        }
      }
      else if (symb == '(' || symb == ')')
      {
        res.data.bracket.scope = symb;
        res.type = PartsOfExpression::BRACKET;
      }
      // else if (symb == '\n')
      // {
      // 	if (!currQ.empty())
      // 	{
      // 		infixQueue.push(currQ);
      // 	}
      // 	continue;
      // }
      else
      {
        res.data.operation.operation = symb;
        res.type = PartsOfExpression::OPERATION;
      }
      currQ.push(res);
    }
    if (!currQ.empty())
    {
      infixQueue.push(currQ);
    }
  }
  in >> std::skipws;
}
