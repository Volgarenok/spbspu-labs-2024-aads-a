#include <iostream>
#include "inputList.hpp"

int main()
{
  using namespace isaychev;
  using myPair = std::pair< std::string, List< size_t > >;
  List< myPair > mainList;
  inputList(std::cin, mainList);
  for (auto i = mainList.begin(); i != mainList.end(); ++i)
  {
    std::cout << (*i).first << " ";
  }
  std::cout << "\n";
}
