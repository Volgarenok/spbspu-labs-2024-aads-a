#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    std::string cmd = argv[1];

    std::ifstream filename(argv[2]);
    if (!filename)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
  }
  else
  {
    std::cerr << "Not enough arguments" << '\n';
    return 2;
  }
  return 0;
}
