#include <iostream>
#include <cstddef>

int main(int argc, char * argv[])
{
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
}

