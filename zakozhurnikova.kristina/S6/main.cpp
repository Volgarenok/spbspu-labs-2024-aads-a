#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <list>
#include <iostream>
#include <string>
#include <list.hpp>
#include "generate.hpp"
#include "sorting.hpp"
#include "print.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  if (argc != 4)
  {
    std::cerr << "No right argument";
    return 1;
  }

  std::string sort = argv[1];
  std::string type = argv[2];
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "You stupid";
    return 1;
  }
  if (type == "ints")
  {
    int array[10000];
    std::generate_n(array, size, RandomNumberInt);

    List< int > biListRealization;
    std::list< int > biListStandart;
    std::deque< int > dequeSort;
    std::deque< int > dequeShaker;
    std::deque< int > dequeShell;
    std::forward_list< int > forwardList;

    for (size_t i = 0; i < size; ++i)
    {
      int number = array[i];
      biListRealization.push_back(number);
      biListStandart.push_front(number);
      dequeSort.push_front(number);
      dequeShaker.push_front(number);
      dequeShell.push_front(number);
      forwardList.push_front(number);
    }
    print(std::cout, forwardList);

    auto beginBiR = biListRealization.begin();
    auto beginDeqSort = dequeSort.begin();
    auto endDeqSort = dequeSort.end();
    auto beginDeqShaker = dequeShaker.begin();
    auto beginDeqShell = dequeShell.begin();

    shaker(++beginBiR, size, std::less< int >());
    biListStandart.sort(std::less< int >());
    std::sort(beginDeqSort, endDeqSort, std::less< int >());
    shaker(++beginDeqShaker, size, std::less< int >());
    shell(beginDeqShell, size, std::less< int >());
    forwardList.sort(std::less< int >());

    print(std::cout, biListRealization);
    print(std::cout, biListStandart);
    print(std::cout, dequeSort);
    print(std::cout, dequeShaker);
    print(std::cout, dequeShell);
    print(std::cout, forwardList);
  }
  else if (type == "floats")
  {}
  else
  {
    std::cerr << "No right type";
    return 1;
  }
}
