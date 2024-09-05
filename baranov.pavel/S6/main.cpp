#include <iostream>
#include <cstddef>
#include <string>
#include <functional>
#include <deque>
#include <list/list.hpp>
#include "sortings.hpp"
#include "sequenceFunctions.hpp"

int main(int argc, char * argv[])
{
  using namespace baranov;
  if (argc < 4)
  {
    std::cerr << "Incorrect CLA\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Size must be greater than zero");
    }

    List< int > nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(1);
    nums.push_back(4);

    insertionSort(nums.begin(), nums.end(), std::less< int >());
    printSequence(nums.cbegin(), nums.cend(), std::cout);
    std::cout << '\n';

    std::deque< int > nums2 = {0, 5, 2, 1, 6, 3, 4};
    quickSort(nums2.begin(), nums2.end(), std::less< int >());
    printSequence(nums2.cbegin(), nums2.cend(), std::cout);
    std::cout << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

