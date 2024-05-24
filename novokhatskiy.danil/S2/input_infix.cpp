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
      switch (symb)
      {
      case '+':
      case '-':
      case '*':
      case '/':
      case '%':
        currQ.push(InfixType(symb));
        break;
      case '(':
      case ')':
        if (symb == '(')
        {
          currQ.push(InfixType::openBracket());
        }
        else
        {
          currQ.push(InfixType::closeBracket());
        }
        break;
      default:
        try
        {
          std::string str = {};
          while (symb != ' ' && symb != '\n')
          {
            str += symb;
            in >> symb;
          }
          currQ.push(InfixType(std::stoll(str)));
          break;
        }
        catch (const std::exception&)
        {
          break;
        }
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
