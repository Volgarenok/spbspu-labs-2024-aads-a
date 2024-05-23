#include <iostream>
#include <iomanip>

#include <tree/twoThreeTree.hpp>

#include "testSorts.hpp"

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Incorrect args\n";
    return 1;
  }

  using namespace zhalilov;
  using testSortFuncType = void (*)(size_t, std::ostream &);
  TwoThree< std::pair< std::string, std::string >, testSortFuncType > testSortVariantsMap;
  testSortVariantsMap[{ "ints", "ascending" }] = testSorts< int, std::less< int > >;
  testSortVariantsMap[{ "ints", "descending" }] = testSorts< int, std::greater< int > >;
  testSortVariantsMap[{ "floats", "ascending" }] = testSorts< float, std::less< float > >;
  testSortVariantsMap[{ "floats", "descending" }] = testSorts< float, std::greater< float > >;
  try
  {
    std::string direction = argv[1];
    std::string type = argv[2];
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("main.cpp: size == 0");
    }
    std::cout << std::fixed << std::setprecision(1);
    testSortVariantsMap[{ type, direction }](size, std::cout);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
