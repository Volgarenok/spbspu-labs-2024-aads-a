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
}