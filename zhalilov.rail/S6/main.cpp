#include <iostream>
#include <cstring>
#include <deque>

#include "randomGenerators.hpp"

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
    if (type == "ints")
    {
      std::deque< int > nums(size);
      fillRandomInts(nums, size);
    }
    else if (type == "floats")
    {
      std::deque< float > nums(size);
      fillRandomFloats(nums, size);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what();
    return 1;
  }
}
