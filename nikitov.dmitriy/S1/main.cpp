#include <iostream>
#include <string>
#include "list.hpp"
#include "iterator.hpp"
#include "input_list.hpp"
#include "output_list.hpp"

int main()
{
  using namespace nikitov;
  List< std::pair< std::string, List< int >* >* > pairsList = inputList(std::cin);
  outputList(pairsList, std::cout);
  return 0;
}
