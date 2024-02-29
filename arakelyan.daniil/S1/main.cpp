#include <iostream>

#include "binList.hpp"
#include "binList.cpp"
#include "node.hpp"
#include "node.cpp"

int main()
{
  using namespace arakelyan;
  using List = BinList<double>;
  using iterator_list = Iterator<double>;

  List list;
  try 
  {
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
    std::cout << "while end. now for\n";
    iterator_list it = list.begin();
    std::cout << *it << "\n";

    for (iterator_list it = list.begin(); it != list.end(); ++it)
    {
      std::cout << *it << " ";
    }
  }
  catch (...)
  {
    std::cerr << "wrong!\n";
    list.clear();
    return 1;
  }

  return 0;
}
