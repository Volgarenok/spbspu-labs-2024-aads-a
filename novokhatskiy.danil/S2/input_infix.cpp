#include "input_infix.hpp"
#include <string>

void novokhatskiy::inputInfix(Queue< Queue< InfixType > >& infixQueue, std::istream& in)
{
  in >> std::noskipws;
  while (!in.eof())
  {
    char symb{};
    Queue< InfixType > currQ;

    while (in >> symb && symb != '\n')
    {
      InfixType res;
      switch (symb)
      {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
        res.type = TokenType::OPERATION;
        res.operation = static_cast<Operation>(symb);
        break;
      case '(':
      case ')':
        res.type = TokenType::BRACKET;
        res.bracket = static_cast<Bracket>(symb);
        break;
      default:
        if (std::isdigit(symb))
        {
          res.type = TokenType::OPERAND;
          std::string str = {};
          str += symb;
          res.operand.num = std::stoll(str);
        }
        break;
      }
      if (symb != ' ')
      {
        currQ.push(res);
      }
    }
    if (!currQ.empty())
    {
      infixQueue.push(currQ);
    }
  }
  in >> std::skipws;
}
