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

    // list.push_front(17);
    // list.printList(std::cout);
    // std::cout << "\n";

    // list.pop_front();
    // list.printList(std::cout);
    // std::cout << "\n";

    // list.push_back(16);
    // list.printList(std::cout);
    // std::cout << "\n";

    // list.pop_back();
    // list.printList(std::cout);
    // std::cout << "\n";

    std::cout << "val in first node of list " << list.getFirst() << "\n";
    std::cout << "val in last node of list " << list.getLast() << "\n";
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
    std::cout << "while end. now another while. loop whith all el in list\n";
    iterator_list  it_b = list.begin();
    std::cout << "it_b = " << *it_b << "\n";
    iterator_list it_l = list.end();
    std::cout << "it_l = " << *it_l << "\n";

    it_b++;
    std::cout <<"it_t++ " << *it_b << "\n";
    it_b++;
    std::cout <<"it_b++ " << *it_b << "\n";
    it_l--;
    std::cout <<"it_l-- " << *it_l << "\n";
    it_l--;
    std::cout <<"it_l-- " << *it_l << "\n";

    for (iterator_list iter = list.begin(); iter != list.end(); iter++)
    {
      std::cout << *iter << " ";
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
