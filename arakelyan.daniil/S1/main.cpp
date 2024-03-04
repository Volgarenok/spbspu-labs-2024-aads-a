#include <__config>
#include <iostream>
#include <stdexcept>

#include "binList.hpp"
#include "binList.cpp"
#include "iterator.hpp"
#include "node.hpp"

int main()
{
  using namespace arakelyan;
  using List = BinList< double >;
  using iterator_list = Iterator< double >;

  List list;
  double var = 1;

  try
  {
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
    } while (var != 0);

    iterator_list it_start = list.begin();
    iterator_list it_end = list.end();
    ++it_start;
    it_end--;

    std::cout << "list_2\n";
    List list_t;
    list_t.assign(it_start, it_end);
    list_t.printList(std::cout);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    list.clear();
    return 1;
  }
  return 0;
}
