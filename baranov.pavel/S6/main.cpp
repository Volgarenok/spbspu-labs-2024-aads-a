#include <iostream>
#include <cstddef>
#include <string>
#include <functional>
#include <deque>
#include <list/list.hpp>
#include "sortings.hpp"

int main(int argc, char * argv[])
{
  using namespace baranov;
  if (argc < 4)
  {
    std::cerr << "Incorrect CLA\n";
    return 1;
  }
  size_t size = 0;
  try
  {
    size = std::stoull(argv[3]);
  }
  catch (const std::exception &)
  {
    std::cerr << "Invalid size\n";
    return 1;
  }

  std::cout << argv[1] << ' ' << argv[2] << ' ' << size << '\n';

  List< int > nums;
  nums.push_back(3);
  nums.push_back(2);
  nums.push_back(5);
  nums.push_back(1);
  nums.push_back(4);
  insertionSort(nums.begin(), nums.end(), std::less< int >());
  for (auto i = nums.cbegin(); i != nums.cend(); ++i)
  {
    std::cout << *i << '\n';
  }

  std::deque< int > nums2 = {0, 5, 2, 1, 6, 3, 4};
  quickSort(nums2.begin(), nums2.end(), std::greater< int >());
  for (auto i = nums2.cbegin(); i != nums2.cend(); ++i)
  {
    std::cout << *i << '\n';
  }
}

