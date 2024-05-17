#include <iostream>
#include "merge.hpp"

int main(int, char**)
{
  using namespace piyavkin;
  List< int > list({1,4,7,2,5,6});
  auto it = ++list.begin();
  ++it;
  ++it;
  List< int > list2;
  merge(list.begin(), it, list.end(), std::less< int >(), list2);
  for (auto x: list2)
  {
    std::cout << x << ' ';
  }
}
