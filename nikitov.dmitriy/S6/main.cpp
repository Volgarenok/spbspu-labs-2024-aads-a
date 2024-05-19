#include <iostream>

int main(int argc, char* argv[])
{
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