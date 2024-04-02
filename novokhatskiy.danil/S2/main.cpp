#include <iostream>
#include <list>
#include <string>
#include "forward_list.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "tokens.hpp"

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
  std::list< Queue< ExpressionType > > expressionList;

  std::cin >> std::noskipws >> std::fixed;
  while (std::cin)
  {
    Queue< ExpressionType > expression;
    std::string line = {};
    char symb = {};
    while (std::cin >> symb)
    {
      ExpressionType type;
      if (symb == ' ' || symb == '\n')
      {
        if (std::isdigit(line[0]))
        {
          type.value.num = std::stoi(line);
          type.part = 0;
        }
        else
        {
          type.value.symb = line[0];
          type.part = 1;
        }
        line = {};
        expression.push(type);
        if (symb == '\n')
        {
          expressionList.push_front(expression);
          break;
        }
      }
      else
      {
        line += symb;
      }
    }
  }
}
