#include <iostream>
#include "merge.hpp"
#include "timsort.hpp"

int main(int argc, char**)
{
  if (argc != 4)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  using namespace piyavkin;
  List< int > list({1,4,7,2,5,6});
  sort_merge(list.begin(), list.end(), std::less< int >());
  for (auto x: list)
  {
    std::cout << x << ' ';
  }
}
