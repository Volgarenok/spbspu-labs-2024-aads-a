#include <iostream>
#include <deque>
#include <forward_list>
#include <algorithm>
#include <list.hpp>
#include "sortings.hpp"
#include "iterators_functions.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  if (argc != 4)
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  size_t size = std::stoull(argv[3]);
  if (size == 0)
  {
    std::cerr << "Error: Wrong size parameter" << '\n';
    return 1;
  }

  std::string sorting = argv[1];
  std::string type = argv[2];
  if (type == "ints")
  {
    std::forward_list< int > fList;
    List< int > firstBiList;
    std::deque< int > firstDeque;
    for (size_t i = 0; i != size; ++i)
    {
      int value = std::rand();
      fList.push_front(value);
      firstBiList.push_back(value);
      firstDeque.push_back(value);
    }
    List< int > secondBiList = firstBiList;
    std::deque< int > secondDeque = firstDeque;
    std::deque< int > thirdDeque = firstDeque;

    printRange(fList.cbegin(), fList.cend(), std::cout);

    if (sorting == "ascending")
    {
      fList.sort(std::less< int >());
      oddEvenSort(firstBiList.begin(), firstBiList.end(), std::less< int >());
      secondBiList.sort(std::greater< int >());
      oddEvenSort(firstDeque.begin(), firstDeque.end(), std::less< int >());
      QSort(secondDeque.begin(), secondDeque.end(), std::less< int >());
      std::sort(thirdDeque.begin(), thirdDeque.end(), std::less< int >());
    }
    else if (sorting == "descending")
    {
      fList.sort(std::greater< int >());
      oddEvenSort(firstBiList.begin(), firstBiList.end(), std::greater< int >());
      secondBiList.sort(std::less< int >());
      oddEvenSort(firstDeque.begin(), firstDeque.end(), std::greater< int >());
      QSort(secondDeque.begin(), secondDeque.end(), std::greater< int >());
      std::sort(thirdDeque.begin(), thirdDeque.end(), std::greater< int >());
    }
    else
    {
      std::cerr << "Error: Wrong sorting parameter" << '\n';
      return 1;
    }
    printRange(fList.cbegin(), fList.cend(), std::cout);
    printRange(firstBiList.cbegin(), firstBiList.cend(), std::cout);
    printRange(secondBiList.cbegin(), secondBiList.cend(), std::cout);
    printRange(firstDeque.cbegin(), firstDeque.cend(), std::cout);
    printRange(secondDeque.cbegin(), secondDeque.cend(), std::cout);
printRange(thirdDeque.cbegin(), thirdDeque.cend(), std::cout);
  }
  else if (type == "floats")
  {
  }
  else
  {
    std::cerr << "Error: Wrong type parameter" << '\n';
    return 1;
  }
  return 0;
}
