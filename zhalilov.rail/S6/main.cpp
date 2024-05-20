#include <iostream>
#include <deque>
#include <iomanip>

#include "randomGenerators.hpp"
#include "testSorts.hpp"

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Incorrect args";
    return 1;
  }

  try
  {
    using namespace zhalilov;
    std::string direction = argv[1];
    std::string type = argv[2];
    size_t size = std::stoull(argv[3]);
    std::cout << std::fixed << std::setprecision(1);
    if (type == "ints")
    {
      std::deque< int > nums(size);
      fillRandomInts(nums, size);
      testSorts(nums, direction, std::cout);
    }
    else if (type == "floats")
    {
      std::deque< float > nums(size);
      fillRandomFloats(nums, size);
      testSorts(nums, direction, std::cout);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what();
    return 1;
  }
}
