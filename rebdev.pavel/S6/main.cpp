#include <iostream>
#include <list>
#include <functional>
#include <ctime>

#include "sort.hpp"

int main(int argv, char ** agrc)
{
  if (argv != 4)
  {
    std::cerr << "Bad input agument number\n";
    return 1;
  }
  std::list< float > newList;
  srand(time(0));
  for (size_t i = 0; i < 10; ++i)
  {
    float a = ((std::rand() % 2000) - 1000);
    std::cout << a << ' ';
    newList.push_back(a);
  }
  std::cout << '\n';
  rebdev::oddEven< float >(newList, std::cout, std::greater< float >());
  return 0;
}
