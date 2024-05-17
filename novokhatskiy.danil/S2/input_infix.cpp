#include "input_infix.hpp"
#include <string>

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
        res.getInfix() = TokenType::OPERATION;
        res.getOperation() = static_cast<Operation>(symb);
        break;
      case '(':
      case ')':
        res.getInfix() = TokenType::BRACKET;
        res.getBracket() = static_cast<Bracket>(symb);
        break;
      default:
        res.getInfix() = TokenType::OPERAND;
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
