#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Invalid args\n";
    return 1;
  }
  size_t size = std::atoi(argv[3]);
  if (size == 0)
  {
    std::cerr << "Invalid size\n";
    return 1;
  }
}
