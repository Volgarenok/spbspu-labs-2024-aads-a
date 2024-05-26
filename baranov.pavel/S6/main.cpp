#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <functional>
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

  std::vector< int > nums = {5, 3, 2, 1, 4};
  insertionSort(nums.begin(), nums.end(), std::less< int >());
  for (auto i = nums.cbegin(); i != nums.cend(); ++i)
  {
    std::cout << *i << '\n';
  }
}

