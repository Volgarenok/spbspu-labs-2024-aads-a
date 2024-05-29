#include <iostream>

#include "sorts.hpp"
#include <list>

int main(int argc, char *argv[])
{
  using namespace gladyshev;
  std::list< int > data = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
  merge(data.begin(), data.end(), std::greater< int >());
  for (int value: data)
  {
    std::cout << value << " ";
  }
  std::cout << "\n";
}
