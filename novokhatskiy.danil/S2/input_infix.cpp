#include "input_infix.hpp"
#include <string>

void novokhatskiy::inputInfix(Queue< Queue< InfixType > >& infixQueue, std::istream& in)
{
  in >> std::noskipws;
  while (in)
  {
    char symb{};
    Queue< InfixType > currQ;
    while (in >> symb && symb != '\n' && !in.eof())
    {
      InfixType res;
      switch (symb)
      {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
        res.getType() = TokenType::OPERATION;
        res.getOp() = static_cast< Operation >(symb);
        break;
      case '(':
      case ')':
        res.getType() = TokenType::BRACKET;
        res.getBracket() = static_cast< Bracket >(symb);
        break;
      default:
        try
        {
          res.getType() = TokenType::OPERAND;
          std::string str = {};
          while (symb != ' ' && symb != '\n')
          {
            str += symb;
            in >> symb;
          }
          res.getOperand().num = std::stoll(str);
          currQ.push(res);
          break;
        }
        catch (const std::exception&)
        {
          break;
        }
      }
      if (symb != ' ' && symb != '\n')
      {
        currQ.push(res);
      }
      if (symb == '\n')
      {
        break;
      }
    }
    if (!currQ.empty())
    {
      infixQueue.push(currQ);
    }
  }
  in >> std::skipws;
}
