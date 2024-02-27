#include <iostream>
#include <string>
#include "list.hpp"
#include "input_list.hpp"
#include "output_list.hpp"

int main()
{
  using namespace nikitov;
  try
  {
    List< std::pair< std::string, List< int > > > pairsList;
    inputList(pairsList, std::cin);
    if (pairsList.size() == 0)
    {
      std::cout << '0' << '\n';
    }
    else
    {
      outputList(pairsList, std::cout);
    }
  }
  catch(std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
