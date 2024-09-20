#include "input_expressions.hpp"
#include <istream>
#include <string>
#include <queue.hpp>
#include "infix_type.hpp"

nikitov::InfixType recognizeType(std::string& line)
{
  if (line[0] == '(')
  {
    return nikitov::InfixType::openBracket();
  }
  else if (line[0] == ')')
  {
    return nikitov::InfixType::closeBracket();
  }
  else if (!std::isdigit(line[0]))
  {
    return nikitov::InfixType(line[0]);
  }
  else
  {
    return nikitov::InfixType(stoll(line));
  }
}

void nikitov::inputExpressions(Queue< Queue< InfixType > >& infixQueue, std::istream& input)
{
  input >> std::noskipws >> std::fixed;
  while (input)
  {
    Queue< InfixType > expression;
    std::string line = {};
    char symb = {};
    while (input >> symb)
    {
      if (symb == ' ')
      {
        expression.push(recognizeType(line));
        line = {};
      }
      else if (symb == '\n')
      {
        if (!line.empty())
        {
          expression.push(recognizeType(line));
          infixQueue.push(expression);
        }
        break;
      }
      else
      {
        line += symb;
      }
    }
  }
  input >> std::skipws >> std::fixed;
}
