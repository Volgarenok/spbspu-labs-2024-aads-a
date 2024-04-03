#include "input_expressions.hpp"
#include <istream>
#include <string>
#include "queue.hpp"
#include "expression_types.hpp"

nikitov::InfixType recognizeType(std::string& line)
{
  if (std::isdigit(line[0]))
  {
    return nikitov::InfixType(nikitov::TypeName::operand, stoll(line));
  }
  else if (line[0] == '(' || line[0] == ')')
  {
    return nikitov::InfixType(nikitov::TypeName::bracket, line[0] == '(');
  }
  else
  {
    return nikitov::InfixType(nikitov::TypeName::operation, line[0]);
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
