#include <iostream>
#include <string>
#include "list.hpp"
#include "iterator.hpp"
#include "input_list.hpp"
#include "output_list.hpp"

int main()
{
  using namespace nikitov;
  try
  {
    List< std::pair< std::string, List< int >* >* > pairsList = inputList(std::cin);
    outputList(pairsList, std::cout);
  }
  catch(...)
  {
    return 1;
  }
  return 0;
}
