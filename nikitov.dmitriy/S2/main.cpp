#include <iostream>
#include <fstream>
#include <list.hpp>
#include "queue.hpp"
#include "expression_type.hpp"
#include "input_list.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  List< Queue< ExpressionType > > expressionList;

  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      inputList(expressionList, input);
    }
    else
    {
      inputList(expressionList, std::cin);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what();
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
