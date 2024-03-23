#include <iostream>
#include <string>
#include <list.hpp>
#include "queue.hpp"
#include "expression_type.hpp"

int main()
{
  using namespace nikitov;
  List< Queue< ExpressionType > > expressionList;

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
          type.storedType = 1;
        }
        else
        {
          type.value.symb = line[0];
          type.storedType = 2;
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

  for (auto i = expressionList.begin(); i != expressionList.end(); ++i)
  {
    while(!((*i).empty()))
    {
      auto value = (*i).drop();
      if (value.storedType == 1)
      {
        std::cout << value.value.num;
      }
      else
      {
        std::cout << value.value.symb;
      }
    }
    std::cout << '\n';
  }
}
