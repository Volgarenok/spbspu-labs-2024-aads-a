#include <iostream>
#include <stdexcept>

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Wrong CLA's number\n";
    return 1;
  }
  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Invalid sequence size");
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
  return 0;
}
