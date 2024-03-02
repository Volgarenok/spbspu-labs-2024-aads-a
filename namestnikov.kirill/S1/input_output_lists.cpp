#include "input_output_lists.hpp"

void namestnikov::inputLists(std::istream & in, ForwardList<pair_t> & dataList)
{
  std::string listName = "";
  int parameter = 0;
  ForwardList<int> parametersList;
  while (in >> listName)
  {
    while (in >> parameter)
    {
      parametersList.push_front(parameter);
    }
    dataList.push_front({listName, parametersList});
  }
}


void namestnikov::outputLists(std::ostream & out, ForwardList<pair_t> & dataList)
{
}
