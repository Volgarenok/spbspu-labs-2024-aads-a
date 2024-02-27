#include <iostream>

#include "binList.hpp"
#include "binList.cpp"

#include "node.hpp"
#include "node.cpp"

int main()
{
  using namespace arakelyan;

  BinList<double> list;
  double var = 1;

  list.push_back(15);
  list.printList(std::cout);
  std::cout << "\n";

  list.push_front(17);
  list.printList(std::cout);
  std::cout << "\n";

  list.pop_front();
  list.printList(std::cout);
  std::cout << "\n";

  list.push_back(16);
  list.printList(std::cout);
  std::cout << "\n";
  
  list.pop_back();
  list.printList(std::cout);
  std::cout << "\n";
  do
  {
    std::cin >> var;

    list.push_back(var);
    list.printList(std::cout);
    std::cout << "\n";
    if (var == 1)
    {
      list.pop_back();
      list.pop_back();
      list.printList(std::cout);
      std::cout << "\n";
    }
    // list.pop_back();
    std::cout << "\n";
    if (var == 3)
    {
      list.clear();
      std::cout << "empty list\n";
    }
  }
  while (var != 0);

  return 0;
}
