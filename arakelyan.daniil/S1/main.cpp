#include <iostream>
#include <stdexcept>

#include "binList.hpp"
#include "binList.cpp"
#include "iterator.hpp"
#include "node.hpp"

int main()
{
  using namespace arakelyan;
  using List = BinList< int >;
  // using iterator_list = Iterator< int >;
  using pair_t = std::pair< std::string, List >;

  BinList< std::pair< std::string, BinList< int > > > list;


  List tempList;
  tempList.assign({1,2,3,4});
  std::string str = "first";

  list.push_back({str, tempList});

  auto it = list.begin();

  pair_t pair = *it;

  List tempOut = pair.second;

  std::cout << pair.first << "\n";
  tempOut.printList(std::cout);
  return 0;
}

