#include <string>
#include "input_infix.hpp"

void novokhatskiy::inputInfix(Queue<Queue<InfixType>>& infixQueue, std::istream& in)
{
  in >> std::noskipws;
  while (in)
  {
    char symb{};
    Queue<InfixType> currQ;
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
          while (symb != ' ' && symb != '\n')
          {
            str += symb;
            in >> symb;
          }
          res.operand.num = std::stoll(str);
          currQ.push(res);
        }
        break;
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
