#include "input_expressions.hpp"
#include <istream>
#include <string>
#include "queue.hpp"
#include "expression_type.hpp"

void recognizeType(nikitov::InfixType& type, std::string& line)
{
  if (std::isdigit(line[0]))
  {
    type.typeName = nikitov::TypeName::operand;
    type.operand.num = stoll(line);
  }
  else if (line[0] == '(' || line[0] == ')')
  {
    type.typeName = nikitov::TypeName::bracket;
    type.bracket.symb = line[0];
  }
  else
  {
    type.typeName = nikitov::TypeName::operation;
    type.operation.symb = line[0];
  }
  line = {};
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
      InfixType type;
      if (symb == ' ')
      {
        recognizeType(type, line);
        expression.push(type);
      }
      else if (symb == '\n')
      {
        if (!line.empty())
        {
          recognizeType(type, line);
          expression.push(type);
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
