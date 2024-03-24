#include "input_list.hpp"
#include <istream>
#include <string>
#include <list.hpp>
#include "queue.hpp"
#include "expression_type.hpp"

void inputExpressionType(nikitov::InfixType& type, std::string& line)
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

void nikitov::inputList(List< Queue< InfixType > >& expressionList, std::istream& input)
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
        inputExpressionType(type, line);
        expression.push(type);
      }
      else if (symb == '\n')
      {
        if (!line.empty())
        {
          inputExpressionType(type, line);
          expression.push(type);
          expressionList.push_front(expression);
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
