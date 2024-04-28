#include <iostream>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }
  std::cout << argv[1];
}
