#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list.hpp>
#include <string>
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

    List< int > countOne;
    std::deque< int > countTwo;
    std::forward_list< int > countThree;

    for (size_t i = 0; i < size; ++i)
    {
      int number = array[i];
      countOne.push_back(number);
      countTwo.push_front(number);
      countThree.push_front(number);
    }
    auto beg = countOne.begin();
    shaker(++beg, size, std::less< int >());
    auto begs = countTwo.begin();
    shell(begs, size);
    countThree.sort(std::less< int >());
    print(std::cout, countOne);
    print(std::cout, countTwo);
    print(std::cout, countThree);
  }
  else if (type == "floats")
  {}
  else
  {
    std::cerr << "No right type";
    return 1;
  }
}
