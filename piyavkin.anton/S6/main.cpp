#include <iostream>
#include <deque>
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
  std::cout << '\n' << detail::get_min_size(68);
  std::deque< int > deq({7,1,5,2,6,0,3});
  timsort(deq.begin(), 7, std::less< int >());
  for (auto x: deq)
  {
    std::cout << x << ' ';
  }
}
